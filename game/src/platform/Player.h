#ifndef PLAYER_H
#define PLAYER_H

#include "../utils/types/vector.h"
#include "raylib.h"
#include "CollisionBox.h"

#include <iostream>

using namespace bowser_util;

constexpr Vector2 PLAYER_SIZE = Vector2{10, 20};
constexpr float COYOTE_TIME = 0.1;

class Player {
public:
    CollisionBox collisionBox = CollisionBox(0, 0, PLAYER_SIZE.x, PLAYER_SIZE.y);
    vec2 velocity = vec2(0, 0);

    float friction = 0.8f;
    float gravity = 1.0f;
    float speed = 1.0f;
    float jump = 12.0f;

    Player();
    void tick(float dt);
    void draw();

    vec2 getPos() const { return vec2(collisionBox.x, collisionBox.y); }
    bool getOnGround() const { return onGround; }

private:
    bool onGround = false;
    double lastOnGroundTime = -99999.0;
};

#endif