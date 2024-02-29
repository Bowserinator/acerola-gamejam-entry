#include "Player.h"
#include "../config.h"

#include <iostream>

void Player::tick(float dt) {
    dt *= GLOBAL_DT_MULTIPLIER;

    velocity += vec2(0, gravity) * dt;
    velocity.x *= friction;

    if (IsKeyDown(KEY_D))
        velocity += vec2(speed, 0) * dt;
    if (IsKeyDown(KEY_A))
        velocity += vec2(-speed, 0) * dt;
    if (IsKeyPressed(KEY_W))
        velocity += vec2(0, -jump) * dt;

    velocity = velocity.clampMagnitude(0.0f, MAX_VELOCITY);
    collisionBox.x += velocity.x * dt;
    collisionBox.y += velocity.y * dt;
}

void Player::draw() {
    DrawRectangle(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, RED);
}
