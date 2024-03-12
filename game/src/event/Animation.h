#ifndef ANIMATION_H
#define ANIMATION_H

#include <functional>
#include "raylib.h"

class Animation {
public:
    Animation() {}
    Animation(float duration): duration(duration), orgDuration(duration) {}

    void start() {
        startTime = GetTime();
        started = true;
        percent = 0.0f;
    }

    void reset() {
        percent = 0.0f;
        duration = orgDuration;
        started = false;
        startTime = 0.0;
    }

    void startOnce() {
        if (!started)
            start();
    }

    void tick() {
        percent = std::min(1.0, (GetTime() - startTime) / duration);
    }

    float progress() {
        return started ? easingFunction(percent) : 0.0f;
    }

    float getDuration() const { return duration; }

    void setDuration(float duration) {
        this->duration = duration;
        orgDuration = duration;
    }

    Animation& setEasingFunction(std::function<float(float)> easingFunction) {
        this->easingFunction = easingFunction;
        return *this;
    }

    std::function<float(float)> easingFunction = [](float x) { return x; };
private:
    float percent = 0.0; // Raw uneased completion percentage 0-1
    float duration = 1.0;
    float orgDuration = 1.0;
    bool started = false;
    double startTime = 0.0;
};

#endif