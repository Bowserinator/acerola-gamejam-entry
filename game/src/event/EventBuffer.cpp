#include "EventBuffer.h"

EventBuffer * EventBuffer::single = nullptr;

void EventBuffer::reset() {
    keyboardEvtConsumed = false;
    gamepadEvtConsumed = false;
    mouseEvtConsumed = false;
}

void EventBuffer::consumeMouse() { mouseEvtConsumed = true; };
void EventBuffer::consumeKeyboard() { keyboardEvtConsumed = true; }
void EventBuffer::consumeGamepad() { gamepadEvtConsumed = true; }

// Input-related functions: keyboard
bool EventBuffer::isKeyPressed(int key, double buffer) {
    if (keyboardEvtConsumed) return false;

    bool recentlyPressed = (GetTime() - getBufferTime(keyPressedEventBuffer, key)) <= buffer;
    bool r = IsKeyPressed(key) || recentlyPressed;
    if (recentlyPressed) // Consume last pressed time
        keyPressedEventBuffer[key] = -999999.0;
    return r;
}

bool EventBuffer::isKeyDown(int key, double buffer) {
    if (keyboardEvtConsumed) return false;

    bool recentlyPressed = (GetTime() - getBufferTime(keyDownEventBuffer, key)) <= buffer;
    bool r = IsKeyDown(key) || recentlyPressed;
    if (recentlyPressed) // Consume last pressed time
        keyDownEventBuffer[key] = -999999.0;
    return r;
}

// Input-related functions: mouse
bool EventBuffer::isMouseButtonPressed(const int button) {
    if (mouseEvtConsumed) return false;
    return IsMouseButtonPressed(button);
}

bool EventBuffer::isMouseButtonReleased(const int button) {
    if (mouseEvtConsumed) return false;
    return IsMouseButtonReleased(button);
}

bool EventBuffer::isMouseButtonDown(const int button) {
    if (mouseEvtConsumed) return false;
    return IsMouseButtonDown(button);
}

bool EventBuffer::isMouseButtonUp(const int button) {
    if (mouseEvtConsumed) return false;
    return IsMouseButtonUp(button);
}

float EventBuffer::getMouseWheelMove() {
    if (mouseEvtConsumed) return 0.0f;
    return GetMouseWheelMove();
}
