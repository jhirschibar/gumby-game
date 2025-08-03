#include <switch.h>
#include <iostream>
#include <memory>
#include "game/GameEngine.h"
#include "graphics/Renderer.h"
#include "input/InputManager.h"
#include "audio/AudioManager.h"
#include "ui/UIManager.h"
#include "utils/Logger.h"
#include "utils/Config.h"

// Global instances
std::unique_ptr<GameEngine> gameEngine;
std::unique_ptr<Renderer> renderer;
std::unique_ptr<InputManager> inputManager;
std::unique_ptr<AudioManager> audioManager;
std::unique_ptr<UIManager> uiManager;

// Game loop variables
bool running = true;
const int TARGET_FPS = 60;
const float FRAME_TIME = 1.0f / TARGET_FPS;

// Initialize Nintendo Switch services
bool initializeSwitch() {
    // Initialize console
    consoleInit(nullptr);
    
    // Initialize graphics
    if (R_FAILED(gfxInitDefault())) {
        Logger::error("Failed to initialize graphics");
        return false;
    }
    
    // Initialize audio
    if (R_FAILED(audrenInit())) {
        Logger::error("Failed to initialize audio");
        return false;
    }
    
    // Initialize input
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    
    Logger::info("Nintendo Switch services initialized successfully");
    return true;
}

// Cleanup Nintendo Switch services
void cleanupSwitch() {
    audrenExit();
    gfxExit();
    consoleExit(nullptr);
    Logger::info("Nintendo Switch services cleaned up");
}

// Initialize game systems
bool initializeGame() {
    try {
        // Initialize configuration
        Config::load("romfs:/config.json");
        
        // Initialize renderer
        renderer = std::make_unique<Renderer>();
        if (!renderer->initialize()) {
            Logger::error("Failed to initialize renderer");
            return false;
        }
        
        // Initialize audio manager
        audioManager = std::make_unique<AudioManager>();
        if (!audioManager->initialize()) {
            Logger::error("Failed to initialize audio manager");
            return false;
        }
        
        // Initialize input manager
        inputManager = std::make_unique<InputManager>();
        if (!inputManager->initialize()) {
            Logger::error("Failed to initialize input manager");
            return false;
        }
        
        // Initialize game engine
        gameEngine = std::make_unique<GameEngine>();
        if (!gameEngine->initialize()) {
            Logger::error("Failed to initialize game engine");
            return false;
        }
        
        // Initialize UI manager
        uiManager = std::make_unique<UIManager>(gameEngine.get(), renderer.get());
        if (!uiManager->initialize()) {
            Logger::error("Failed to initialize UI manager");
            return false;
        }
        
        Logger::info("Game systems initialized successfully");
        return true;
        
    } catch (const std::exception& e) {
        Logger::error("Exception during game initialization: " + std::string(e.what()));
        return false;
    }
}

// Main game loop
void gameLoop() {
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    
    while (running && appletMainLoop()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
        
        // Cap frame time to prevent spiral of death
        if (deltaTime > FRAME_TIME) {
            deltaTime = FRAME_TIME;
        }
        
        // Handle input
        inputManager->update();
        
        // Check for quit command
        if (inputManager->isQuitRequested()) {
            running = false;
            break;
        }
        
        // Update game logic
        gameEngine->update(deltaTime);
        
        // Update UI
        uiManager->update(deltaTime);
        
        // Begin frame rendering
        renderer->beginFrame();
        
        // Render game
        gameEngine->render(renderer.get());
        
        // Render UI
        uiManager->render(renderer.get());
        
        // End frame rendering
        renderer->endFrame();
        
        // Update audio
        audioManager->update();
        
        // Frame rate limiting
        auto frameEndTime = std::chrono::high_resolution_clock::now();
        auto frameDuration = std::chrono::duration<float>(frameEndTime - currentTime).count();
        
        if (frameDuration < FRAME_TIME) {
            auto sleepTime = std::chrono::duration<float>(FRAME_TIME - frameDuration);
            std::this_thread::sleep_for(sleepTime);
        }
        
        lastFrameTime = currentTime;
    }
}

// Handle application lifecycle
void handleAppletMessage() {
    AppletMessage msg;
    if (R_SUCCEEDED(appletGetMessage(&msg))) {
        switch (msg) {
            case AppletMessage_FocusStateChanged:
                // Handle focus state changes
                break;
            case AppletMessage_OperationModeChanged:
                // Handle operation mode changes (docked/undocked)
                renderer->onOperationModeChanged();
                break;
            case AppletMessage_UserTimeChanged:
                // Handle user time changes
                break;
            case AppletMessage_MessageEnd:
                // Handle message end
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    Logger::info("Starting Jody-Tama for Nintendo Switch");
    
    // Initialize Switch services
    if (!initializeSwitch()) {
        Logger::error("Failed to initialize Switch services");
        return -1;
    }
    
    // Initialize game systems
    if (!initializeGame()) {
        Logger::error("Failed to initialize game systems");
        cleanupSwitch();
        return -1;
    }
    
    Logger::info("Starting game loop");
    
    // Main game loop
    gameLoop();
    
    Logger::info("Game loop ended, cleaning up");
    
    // Cleanup
    uiManager.reset();
    gameEngine.reset();
    inputManager.reset();
    audioManager.reset();
    renderer.reset();
    
    cleanupSwitch();
    
    Logger::info("Jody-Tama shutdown complete");
    return 0;
}