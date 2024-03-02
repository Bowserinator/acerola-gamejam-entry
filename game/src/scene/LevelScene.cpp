#include "../platform/Player.h"
#include "../platform/CollisionBox.h"
#include "../event/EventBuffer.h"
#include "LevelSceneManager.h"
#include "LevelScene.h"

void LevelScene::init() {
    player->init();
}

void LevelScene::tick(float dt) {
    if (GetFrameTime() > 0.1) return; // Delta time was too big, maybe user tabbed out?
    scene.update();

    dialogManager.update();
    if (!dialogBox->getHidden()) {
        EventBuffer::ref()->consumeKeyboard();
        EventBuffer::ref()->consumeMouse();
    }

    player->tick(dt);
    for (const auto &collider : colliders)
        player->collisionBox.pushSelfOutsideOf(collider, player->velocity);
    for (auto &collider : interactiveColliders)
        collider.isColliding(player->collisionBox);

    for (auto &animation : animations)
        animation.tick();

    // Switch scene on fade out
    if (animations[1].progress() == 1.0f)
        parent->switchScene(nextScene);
}

void LevelScene::draw() {
    BeginMode2D(camera);
    player->draw();
    for (const auto &collider : colliders)
        DrawRectangleLines(collider.x, collider.y, collider.width, collider.height, GREEN);
    for (const auto &collider : interactiveColliders)
        DrawRectangleLines(collider.x, collider.y, collider.width, collider.height, BLUE);
    EndMode2D();

    scene.draw();

    // Fade animation
    float fade = std::max(1.0f - animations[0].progress(), animations[1].progress());
    if (fade > 0.0)
        DrawRectangle(0, 0, screenWidth, screenHeight, Color{ 0, 0, 0, (unsigned char)std::round(255 * fade) });

    #ifdef DEBUG
    DrawFPS(10, 10);
    #endif
}
