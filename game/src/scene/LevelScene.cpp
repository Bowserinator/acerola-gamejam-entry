#include "../platform/Player.h"
#include "../platform/CollisionBox.h"
#include "LevelScene.h"

void LevelScene::tick(float dt) {
    scene.update();

    player->tick(dt);

    for (const auto &collider : colliders) {
        player->collisionBox.pushSelfOutsideOf(collider, player->velocity);
    }

    // TODO
    if (IsKeyPressed(KEY_P))
        dialogBox->setText("This is another example line");
}

void LevelScene::draw() {
    ClearBackground(BLACK);
    player->draw();
    for (const auto &collider : colliders)
        DrawRectangle(collider.x, collider.y, collider.width, collider.height, GREEN);
    scene.draw();

    DrawFPS(10, 10);
}
