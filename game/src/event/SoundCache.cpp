#include "SoundCache.h"
#include "raylib.h"
#include "../config.h"

void SoundCache::init() {
    if (_init) return;

    buttonHover = LoadSound("resources/sounds/hover.wav");
    chatBeep = LoadSound("resources/sounds/beep.wav");
    click = LoadSound("resources/sounds/click.wav");
    correct = LoadSound("resources/sounds/correct.wav");
    wrong = LoadSound("resources/sounds/wrong.wav");
    yay = LoadSound("resources/sounds/yay.wav");
    tick = LoadSound("resources/sounds/tick.wav");
    footsteps = LoadSound("resources/sounds/footsteps.wav");
    horn = LoadSound("resources/sounds/horn.mp3");
    night = LoadSound("resources/sounds/night-ambiance.mp3");
    car = LoadSound("resources/sounds/car.mp3");

    SetSoundVolume(correct, 1.1);

    _init = true;
}

SoundCache::~SoundCache() {
    UnloadSound(buttonHover);
    UnloadSound(chatBeep);
    UnloadSound(click);
}
