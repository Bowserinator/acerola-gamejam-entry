#ifndef PLAYER_H
#define PLAYER_H

#include "../utils/types/vector.h"
#include "raylib.h"
#include "CollisionBox.h"

#include <iostream>

using namespace bowser_util;

constexpr Vector2 PLAYER_SIZE = Vector2{10, 20};

class Player {
public:
    CollisionBox collisionBox = CollisionBox(0, 0, PLAYER_SIZE.x, PLAYER_SIZE.y)
        .setOnPush([this](const CollisionBox &other, const CollisionBox::FACE face) {
            if (face == CollisionBox::FACE::LEFT || face == CollisionBox::FACE::RIGHT)
                velocity.x = 0;
            else {
                velocity.y = 0;
            }
        });
    vec2 velocity = vec2(0, 0);

    Player() {}
    void tick(float dt);
    void draw();

    vec2 getPos() { return vec2(collisionBox.x, collisionBox.y); }
};

#endif