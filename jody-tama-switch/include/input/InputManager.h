#pragma once

#include <switch.h>
#include <vector>
#include <string>

// Input types
enum class InputType {
    BUTTON_PRESS,
    BUTTON_RELEASE,
    BUTTON_HOLD,
    AXIS_MOVE,
    TOUCH_DOWN,
    TOUCH_UP,
    TOUCH_MOVE
};

// Button definitions
enum class Button {
    A,
    B,
    X,
    Y,
    L,
    R,
    ZL,
    ZR,
    PLUS,
    MINUS,
    HOME,
    CAPTURE,
    LEFT_STICK,
    RIGHT_STICK,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT
};

// Input event structure
struct InputEvent {
    InputType type;
    Button button;
    float value; // For analog inputs
    int x, y;    // For touch inputs
    float timestamp;
    
    InputEvent(InputType t, Button b, float v = 0.0f, int posX = 0, int posY = 0)
        : type(t), button(b), value(v), x(posX), y(posY), timestamp(0.0f) {}
};

// Input state
struct InputState {
    bool buttons[18]; // All buttons
    float leftStickX, leftStickY;
    float rightStickX, rightStickY;
    bool touchActive;
    int touchX, touchY;
    
    InputState() {
        for (int i = 0; i < 18; i++) {
            buttons[i] = false;
        }
        leftStickX = leftStickY = rightStickX = rightStickY = 0.0f;
        touchActive = false;
        touchX = touchY = 0;
    }
};

class InputManager {
public:
    InputManager();
    ~InputManager();
    
    // Initialization
    bool initialize();
    void shutdown();
    
    // Update and polling
    void update();
    void pollInput();
    
    // Input state queries
    bool isButtonPressed(Button button) const;
    bool isButtonReleased(Button button) const;
    bool isButtonHeld(Button button) const;
    float getAxisValue(Button axis) const;
    bool isTouchActive() const;
    void getTouchPosition(int& x, int& y) const;
    
    // Event handling
    std::vector<InputEvent> getEvents() const;
    void clearEvents();
    
    // Game-specific input
    bool isConfirmPressed() const;
    bool isCancelPressed() const;
    bool isMenuPressed() const;
    bool isQuitRequested() const;
    
    // Navigation
    bool isUpPressed() const;
    bool isDownPressed() const;
    bool isLeftPressed() const;
    bool isRightPressed() const;
    
    // Analog stick
    float getLeftStickX() const;
    float getLeftStickY() const;
    float getRightStickX() const;
    float getRightStickY() const;
    
    // Touch screen
    bool isTouchDown() const;
    bool isTouchUp() const;
    bool isTouchMove() const;
    
    // Utility
    void setDeadZone(float deadZone);
    float getDeadZone() const;
    void setRepeatDelay(float delay);
    float getRepeatDelay() const;
    
private:
    // Input state
    InputState currentState;
    InputState previousState;
    std::vector<InputEvent> events;
    
    // Configuration
    float deadZone;
    float repeatDelay;
    float repeatRate;
    
    // Timing
    float lastUpdateTime;
    std::unordered_map<Button, float> buttonPressTimes;
    std::unordered_map<Button, float> buttonRepeatTimes;
    
    // Switch-specific
    PadState padState;
    HidTouchScreenState touchState;
    
    // Private methods
    void processPadInput();
    void processTouchInput();
    void processButtonInput(Button button, bool pressed);
    void processAxisInput(Button axis, float value);
    void processTouchInput(int x, int y, bool active);
    
    // Utility
    int buttonToIndex(Button button) const;
    Button indexToButton(int index) const;
    bool isAxis(Button button) const;
    float applyDeadZone(float value) const;
    bool shouldRepeat(Button button) const;
    
    // Event generation
    void addEvent(InputType type, Button button, float value = 0.0f, int x = 0, int y = 0);
};