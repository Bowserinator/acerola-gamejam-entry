#ifndef SOUND_CACHE_H
#define SOUND_CACHE_H

#include "raylib.h"

class SoundCache {
public:
    Sound buttonHover, chatBeep, click, correct, wrong, yay, tick, footsteps, horn, night, car;

    Music title, bgMusic;

    SoundCache(SoundCache &other) = delete;
    void operator=(const SoundCache&) = delete;
    ~SoundCache();

    // Call after OpenGL context has been initialized
    void init();

    static SoundCache * ref() {
        if (single == nullptr) [[unlikely]]
            single = new SoundCache;
        return single;
    };

    static void destroy() {
        delete single;
        single = nullptr;
    }
private:
    bool _init;
    inline static SoundCache * single = nullptr;

    SoundCache(): _init(false) {}
};

#endif