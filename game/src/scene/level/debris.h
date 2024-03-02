#ifndef DEBRIS_H
#define DEBRIS_H

#include "../../utils/types/vector.h"
#include "../../event/Animation.h"
#include <functional>

using namespace bowser_util;

class LevelScene;
class Debris {
public:
    void tick(float dt);
    void draw();

    std::function<void(LevelScene*)> onComplete = [](LevelScene*) {};
    float rotation = 0.0f;
    float startRotation = 0.0f;
    float targetRotation = 0.0f;
    vec2 pos, startPos, targetPos;
    Animation moveAnimation;
};

#endif