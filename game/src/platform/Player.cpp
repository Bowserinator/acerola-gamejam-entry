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

void Player::init() {
    if (!loaded) {
        Image bgImg = LoadImage("resources/img/player1.png");
        Image bgImg2 = LoadImage("resources/img/player2.png");
        playerImage = LoadTextureFromImage(bgImg);
        playerImage2 = LoadTextureFromImage(bgImg2);
        UnloadImage(bgImg);
        UnloadImage(bgImg2);
        loaded = true;
    }
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

    if (isDash && EventBuffer::ref()->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        const vec2 dir = (vec2(GetMousePosition()) - getPos()).normalize();
        velocity = dir * 20.0f;
    }

    if (!isDash) {
        recentlyOnGround = GetTime() - lastOnGroundTime < COYOTE_TIME; // Update again
        velocity += vec2(0, recentlyOnGround ? 0.01 : gravity) * dt;
        velocity.x *= friction;
    } else {
        velocity *= frictionAir;
    }

    onGround = false;
    velocity = velocity.clampMagnitude(0.0f, MAX_VELOCITY);
    collisionBox.x += velocity.x * dt;
    collisionBox.y += velocity.y * dt;
}

void Player::draw() {
    // DrawRectangle(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, 
    //     onGround ? BLUE : RED);

    if (GetTime() - lastWalkCycle > 0.2) {
        lastWalkCycle = GetTime();
        walkCycle = 1 - walkCycle;
    }

    auto &tex = velocity.lengthSqr() > 0.01 ? 
        (walkCycle ? playerImage : playerImage2) : 
        playerImage;
    const Rectangle source = velocity.x < 0.0f ?
        Rectangle{ 0.0f, 0.0f, (float)tex.width, (float)tex.height } :
        Rectangle{ 0.0f, 0.0f, (float)-tex.width, (float)tex.height };
    const Rectangle dest{ collisionBox.x - collisionBox.width / 4, collisionBox.y + 5, collisionBox.width * 2 * scale, collisionBox.height * scale };
    DrawTexturePro(tex, source, dest, vec2(0), 0.0f, WHITE);
}
