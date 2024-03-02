#include "TimeLevelScene.h"
#include "../platform/Player.h"

void TimeLevelScene::restart() {
    states.clear();
    reversingTime = false;

    // TODO: reset player location
}

void TimeLevelScene::tick(float dt) {
    LevelScene::tick(dt);

    if (IsKeyPressed(KEY_P) && !reversingTime) {
        reversingTime = true;
    }

    if (reversingTime) {
        if (states.size() > 1)
            states.pop_back();
    } else {
        auto playerPos = player->getPos();
        states.emplace_back(playerPos.x, playerPos.y);
        if (states.size() >= MAX_STATES)
            restart();
    }
}

void TimeLevelScene::draw() {
    LevelScene::draw();
    auto &state = states[states.size() - 1];
    if (reversingTime) {
        BeginMode2D(camera);
        DrawRectangleLines(state.playerX, state.playerY, player->collisionBox.width, player->collisionBox.height, PURPLE);
        EndMode2D();
    }
}
