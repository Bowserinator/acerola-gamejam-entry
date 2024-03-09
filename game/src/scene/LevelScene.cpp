#include "../platform/Player.h"
#include "../platform/CollisionBox.h"
#include "../event/EventBuffer.h"
#include "LevelSceneManager.h"
#include "LevelScene.h"
#include "../memory/NewsImages.h"
#include "../utils/graphics.h"

void LevelScene::init() {
    player->init();

    if (!IsShaderReady(playerLightShader)) {
        playerLightShader = LoadShader(nullptr, "resources/shaders/playerLight.fs");
        lightTextureLoc = GetShaderLocation(playerLightShader, "lightTexture");
        lightTextureRectLoc = GetShaderLocation(playerLightShader, "lightTextureRegion");
    }
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

    auto getLightMapTextureRect = [this](Texture2D &tex) {
        auto pos = player->getPos();
        return Vector4{
            pos.x / tex.width,
            pos.y / tex.height,
            player->collisionBox.width / tex.width,
            player->collisionBox.height / tex.height
        };
    };

    if (lightMapId == 1) {
        BeginShaderMode(playerLightShader);
        SetShaderValueTexture(playerLightShader, lightTextureLoc, NewsImageCache::ref()->apartmentLights);
        bowser_util::setShaderValue(playerLightShader, lightTextureRectLoc, getLightMapTextureRect(
            NewsImageCache::ref()->apartmentLights ));
        player->draw();
        EndShaderMode();
    } else if (lightMapId == 2) {
        BeginShaderMode(playerLightShader);
        SetShaderValueTexture(playerLightShader, lightTextureLoc, NewsImageCache::ref()->outsideLights);
        bowser_util::setShaderValue(playerLightShader, lightTextureRectLoc, getLightMapTextureRect(
            NewsImageCache::ref()->outsideLights ));
        player->draw();
        EndShaderMode();
    } else {
        player->draw();
    }

#ifdef DEBUG
    for (const auto &collider : colliders)
        DrawRectangleLines(collider.x, collider.y, collider.width, collider.height, GREEN);
    for (const auto &collider : interactiveColliders)
        DrawRectangleLines(collider.x, collider.y, collider.width, collider.height, BLUE);
#endif
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

void LevelScene::onSwitchTo() {
    player->setPos(vec2(150, 150));
    for (auto i = 0; i < animations.size(); i++)
        animations[i].reset();
    animations[0].start(); // Fade in
    player->velocity = vec2(0.);
    player->scale = 1.0f;
}
