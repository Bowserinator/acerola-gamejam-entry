#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include "raylib.h"
#include <map>

// A circular queue of events
class EventBuffer {
public:
    EventBuffer(EventBuffer&other) = delete;
    void operator=(const EventBuffer&) = delete;
    ~EventBuffer() = default;

    void reset();
    void consumeMouse();
    void consumeKeyboard();
    void consumeGamepad();

    // Input-related functions: keyboard
    bool isKeyPressed(int key, double buffer=0.0);
    bool isKeyDown(int key, double buffer=0.0);
    void bufferKeyPressed(int key) { keyPressedEventBuffer[key] = GetTime(); }
    void bufferKeyDown(int key) { keyDownEventBuffer[key] = GetTime(); }

    // Input-related functions: mouse
    bool isMouseButtonPressed(const int button);
    bool isMouseButtonReleased(const int button);
    bool isMouseButtonDown(const int button);
    bool isMouseButtonUp(const int button);
    float getMouseWheelMove();

    static EventBuffer * ref() {
        if (single == nullptr) [[unlikely]]
            single = new EventBuffer;
        return single;
    };

    static void destroy() {
        delete single;
        single = nullptr;
    }
private:
    bool keyboardEvtConsumed;
    bool gamepadEvtConsumed;
    bool mouseEvtConsumed;

    // Key code: last time
    std::map<int, double> keyDownEventBuffer;
    std::map<int, double> keyPressedEventBuffer;

    // Key key from buffer defaulting to -INF
    double getBufferTime(const std::map<int, double> &map, const int key) {
        const auto itr = map.find(key);
        if (itr == map.end()) return -999999.0;
        return itr->second;
    }

    static EventBuffer * single;

    EventBuffer():
        keyboardEvtConsumed(false),
        gamepadEvtConsumed(false),
        mouseEvtConsumed(false) {}
};

#endif