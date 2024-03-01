#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "raylib.h"
#include <functional>
#include "../utils/types/vector.h"

using namespace bowser_util;

class Player;
class LevelScene;

class CollisionBox {
public:
    enum class FACE { TOP, BOTTOM, LEFT, RIGHT };

    float x, y, width, height;
    std::function<void(const CollisionBox&)> onCollide = [](const CollisionBox&){}; // Called on collision
    std::function<void(const CollisionBox&, const FACE)> onPush = [](const CollisionBox&, const FACE){}; // Called on push

    CollisionBox(): x(0), y(0), width(0), height(0) {};
    CollisionBox(float x, float y, float width, float height): x(x), y(y), width(width), height(height) {}
    operator Rectangle() const { return Rectangle{ x, y, width, height }; }

    CollisionBox &setOnCollide(std::function<void(const CollisionBox&)> onCollide) { this->onCollide = onCollide; return *this; }
    CollisionBox &setOnPush(std::function<void(const CollisionBox&, const FACE)> onPush) {
        this->onPush = onPush; return *this;
    }

    // @param Rectangle other Other "static" collision box
    // @param vec2 Velocity moving into, used for hint for what side to push to
    // Moves self outside to nearest point outside of other rectangle
    void pushSelfOutsideOf(const CollisionBox &other, const vec2 &velHint);

    // @param Other rectangle to compare to
    // Is self colliding?
    bool isColliding(const CollisionBox &other);
};

#endif