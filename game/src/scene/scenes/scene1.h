#ifndef SCENE1_H
#define SCENE1_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsImages.h"
#include "../../event/SoundCache.h"

class Player;

class Scene1: public LevelScene {
public:
    Scene1(Player * player): LevelScene(player) {
        camera.zoom = 2.5;

        const std::string NPCTitle = "Taxi Driver";
        nextScene = 5;

        dialogManager.addNode(DialogManager::Node(1, 2, "Who was that girl at the hospital?...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 3, "I can't remember... I might be too tired, or drunk... but is everything backwards?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(3, 4, "It's getting late, I should head back to my apartment.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 0, "How convenient, there's a taxi there.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.addNode(DialogManager::Node(5, 6, "Forget it, I'm gonna go take my break!")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(6, 7, "...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "We just left from there.")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(8, 9, "What? Can you take me to this address?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(9, 10, "We're here.")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(10, 11, "(Wait... if time is reversed, then maybe this taxi will take me back home)")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.addNode(DialogManager::Node(11, 12, "(The driver hands me a wad of cash and starts driving)")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(12, 0, "")
            .setOnActive([this](DialogManager::Node&) {
                animations[1].startOnce(); // Fade out
                PlaySound(SoundCache::ref()->car);
                StopSound(SoundCache::ref()->night);
            }));
        dialogManager.jumpToNode(1);

        colliders.emplace_back(0, 195, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        colliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);

        interactiveColliders.emplace_back(screenWidth / 2 / camera.zoom, 0, 200, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            showPrompt = true;
            if (IsKeyPressed(KEY_X) && dialogBox->getHidden() && animations[1].progress() == 0.0f)
                dialogManager.jumpToNode(5);
        };

        lightMapId = 2;
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        PlaySound(SoundCache::ref()->horn);
        PlaySound(SoundCache::ref()->night);
    }

    virtual void draw() override {
        BeginMode2D(camera);
        DrawTexture(bg, 0, 10, WHITE);
        EndMode2D();
        
        if (showPrompt)
            DrawTextureEx(
                NewsImageCache::ref()->interactTexture,
                Vector2{ (float)screenWidth * 0.66f, 320 },
                0.0, 0.8f, WHITE
            );
        LevelScene::draw();
        showPrompt = false;
    }

    virtual void init() {
        LevelScene::init();
        Image bgImg = LoadImage("resources/img/outside.png");
        bg = LoadTextureFromImage(bgImg);
        UnloadImage(bgImg);
    };

private:
    Texture2D bg;
    bool showPrompt = false;
};

#endif