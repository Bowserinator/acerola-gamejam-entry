#include "Player.h"
#include "../config.h"
#include "../event/EventBuffer.h"

#include <iostream>

Player::Player() {
    auto onPush = [this](const CollisionBox &other, const CollisionBox::FACE face) {
        if (face == CollisionBox::FACE::LEFT || face == CollisionBox::FACE::RIGHT)
            velocity.x = 0;
        else {
            velocity.y = 0;
            onGround = true;
            lastOnGroundTime = GetTime();
        }
    };
    collisionBox.setOnPush(onPush);
}

void Player::tick(float dt) {
    dt *= GLOBAL_DT_MULTIPLIER;

    bool recentlyOnGround = GetTime() - lastOnGroundTime < COYOTE_TIME;

    if (EventBuffer::ref()->isKeyDown(KEY_D))
        velocity += vec2(speed, 0) * dt;
    if (EventBuffer::ref()->isKeyDown(KEY_A))
        velocity += vec2(-speed, 0) * dt;
    if (EventBuffer::ref()->isKeyPressed(KEY_W, 0.05)) {
        // Buffer inputs if can't jump at the moment
        if (recentlyOnGround) {
            velocity += vec2(0, -jump) * dt;
            lastOnGroundTime = -99999.0;
        } else
            EventBuffer::ref()->bufferKeyPressed(KEY_W);
    }

    recentlyOnGround = GetTime() - lastOnGroundTime < COYOTE_TIME; // Update again
    velocity += vec2(0, recentlyOnGround ? 0.01 : gravity) * dt;
    velocity.x *= friction;

    onGround = false;
    velocity = velocity.clampMagnitude(0.0f, MAX_VELOCITY);
    collisionBox.x += velocity.x * dt;
    collisionBox.y += velocity.y * dt;
}

void Player::draw() {
    DrawRectangle(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, 
        onGround ? BLUE : RED);
}
