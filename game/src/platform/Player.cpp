#include "Player.h"

#include <iostream>

void Player::tick(float dt) {
    // Apply gravity
    // TODO: gravity property?
    velocity += vec2(0, 1); // TODO gravity value + dt

    if (IsKeyDown(KEY_D))
        velocity += vec2(1, 0);
    if (IsKeyDown(KEY_A))
        velocity += vec2(-1, 0);
    if (IsKeyPressed(KEY_W))
        velocity += vec2(0, -12);

    velocity.x *= 0.8;

    collisionBox.x += velocity.x;
    collisionBox.y += velocity.y;
}

void Player::draw() {
    DrawRectangle(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, RED);
}
