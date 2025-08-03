#pragma once

#include <memory>
#include <vector>
#include <string>
#include "game/GameEngine.h"
#include "graphics/Renderer.h"

// Forward declarations
class GameEngine;
class Renderer;

// UI states
enum class UIState {
    MAIN_MENU,
    GAME_PLAYING,
    PAUSE_MENU,
    GAME_OVER,
    SETTINGS,
    RULES,
    CREDITS
};

// UI element types
enum class UIElementType {
    BUTTON,
    LABEL,
    PANEL,
    BOARD,
    CARD,
    MODAL
};

// UI element base class
class UIElement {
public:
    UIElement(float x, float y, float width, float height);
    virtual ~UIElement();
    
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer* renderer) = 0;
    virtual bool handleInput(float x, float y, bool pressed) = 0;
    
    // Properties
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    void setPosition(float newX, float newY);
    void setSize(float newWidth, float newHeight);
    
    // Visibility
    bool isVisible() const { return visible; }
    void setVisible(bool visible) { this->visible = visible; }
    
    // Interaction
    bool isEnabled() const { return enabled; }
    void setEnabled(bool enabled) { this->enabled = enabled; }
    
protected:
    float x, y, width, height;
    bool visible;
    bool enabled;
};

// Button UI element
class UIButton : public UIElement {
public:
    UIButton(float x, float y, float width, float height, const std::string& text);
    
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    bool handleInput(float x, float y, bool pressed) override;
    
    void setText(const std::string& text);
    void setCallback(std::function<void()> callback);
    
private:
    std::string text;
    std::function<void()> callback;
    bool pressed;
    bool hovered;
};

// Label UI element
class UILabel : public UIElement {
public:
    UILabel(float x, float y, float width, float height, const std::string& text);
    
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    bool handleInput(float x, float y, bool pressed) override { return false; }
    
    void setText(const std::string& text);
    void setColor(float r, float g, float b, float a);
    
private:
    std::string text;
    float r, g, b, a;
};

// Game board UI element
class UIBoard : public UIElement {
public:
    UIBoard(float x, float y, float width, float height, GameEngine* gameEngine);
    
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    bool handleInput(float x, float y, bool pressed) override;
    
    void setSelectedSquare(int row, int col);
    void setValidMoves(const std::vector<std::pair<int, int>>& moves);
    
private:
    GameEngine* gameEngine;
    int selectedRow, selectedCol;
    std::vector<std::pair<int, int>> validMoves;
    
    void renderBoard(Renderer* renderer);
    void renderPieces(Renderer* renderer);
    void renderSelection(Renderer* renderer);
    void renderValidMoves(Renderer* renderer);
    
    std::pair<int, int> screenToBoard(float screenX, float screenY) const;
};

// Card UI element
class UICard : public UIElement {
public:
    UICard(float x, float y, float width, float height, const std::string& cardName);
    
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    bool handleInput(float x, float y, bool pressed) override;
    
    void setCardName(const std::string& cardName);
    void setSelected(bool selected);
    void setEnabled(bool enabled);
    
private:
    std::string cardName;
    bool selected;
    bool enabled;
    
    void renderCardPattern(Renderer* renderer);
};

class UIManager {
public:
    UIManager(GameEngine* gameEngine, Renderer* renderer);
    ~UIManager();
    
    // Initialization
    bool initialize();
    void shutdown();
    
    // Update and rendering
    void update(float deltaTime);
    void render(Renderer* renderer);
    
    // State management
    void setState(UIState state);
    UIState getState() const;
    
    // Input handling
    bool handleInput(float x, float y, bool pressed);
    bool handleButtonPress(Button button);
    
    // UI creation
    void createMainMenu();
    void createGameUI();
    void createPauseMenu();
    void createGameOverScreen();
    void createSettingsMenu();
    void createRulesScreen();
    
    // Game-specific UI
    void updateGameInfo();
    void updateTurnIndicator();
    void updateCardDisplay();
    void showGameOverModal(const std::string& winner, VictoryCondition condition);
    void hideGameOverModal();
    
    // Utility
    void showMessage(const std::string& message, float duration = 3.0f);
    void hideMessage();
    
private:
    GameEngine* gameEngine;
    Renderer* renderer;
    
    // UI state
    UIState currentState;
    std::vector<std::unique_ptr<UIElement>> elements;
    
    // Game UI elements
    UIBoard* gameBoard;
    std::vector<UICard*> playerCards;
    UICard* centerCard;
    UILabel* turnIndicator;
    UILabel* gameStatus;
    
    // Menu elements
    UIButton* newGameButton;
    UIButton* settingsButton;
    UIButton* rulesButton;
    UIButton* quitButton;
    
    // Modal elements
    UIElement* gameOverModal;
    UIElement* pauseModal;
    UIElement* settingsModal;
    
    // Message display
    UILabel* messageLabel;
    float messageTimer;
    bool messageVisible;
    
    // Private methods
    void clearElements();
    void createElement(std::unique_ptr<UIElement> element);
    
    // Callback functions
    void onNewGameClicked();
    void onSettingsClicked();
    void onRulesClicked();
    void onQuitClicked();
    void onResumeClicked();
    void onMainMenuClicked();
    
    // Layout helpers
    void layoutMainMenu();
    void layoutGameUI();
    void layoutPauseMenu();
    void layoutGameOverScreen();
    
    // Utility
    void centerElement(UIElement* element, float containerWidth, float containerHeight);
    void arrangeCardsHorizontally(std::vector<UICard*>& cards, float startX, float y, float spacing);
};