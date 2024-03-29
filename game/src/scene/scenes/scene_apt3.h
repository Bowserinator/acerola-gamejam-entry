#ifndef SCENE_APT3_H
#define SCENE_APT3_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsImages.h"

class Player;

class SceneApt3: public LevelScene {
public:
    SceneApt3(Player * player): LevelScene(player) {
        camera.zoom = 2.5;
        camera.offset = vec2(0, 20);

        const std::string NOTE_TITLE = "Note";

        dialogManager.addNode(DialogManager::Node(1, 15, "Uhh... I can never get used to time reversed eating")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(15, 2, "Or going to the bathroom...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 6, "Let's see if I wrote anything to myself...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.addNode(DialogManager::Node(6, 7, "Hey so you've reached the debut stream, where she became famous.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "This is all long term predictions so there's no way that she would know unless she lived to be over a hundred.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 11, "There were some aberrant time loops during this, so make sure to answer consistently! Good luck.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(11, 0, "")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR)
            .addChoice("Begin final round", 9));

        dialogManager.addNode(DialogManager::Node(9, 0, "")
            .setOnActive([this](DialogManager::Node&){
                dialogManager.jumpToNode(0);
                StopMusicStream(SoundCache::ref()->bgMusic);
                animations[1].startOnce(); // Fade out
            }));

        colliders.emplace_back(0, 150, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        colliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);
        interactiveColliders.emplace_back(screenWidth / 2 / camera.zoom, 0, 100, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            showPrompt = true;
            if (IsKeyPressed(KEY_X) && dialogBox->getHidden() && animations[1].progress() == 0.0f)
                dialogManager.jumpToNode(1);
        };

        nextScene = 8;
    }

    virtual void draw() override {
        UpdateMusicStream(SoundCache::ref()->bgMusic);

        BeginMode2D(camera);
        DrawTexture(NewsImageCache::ref()->apartmentBackground, 0, 10, WHITE);
        if (showPrompt)
            DrawTextureEx(
                NewsImageCache::ref()->Xprompt,
                Vector2{ screenWidth / 2 / camera.zoom - 10, 100 },
                0.0, 0.8f / camera.zoom, WHITE
            );
        EndMode2D();
        
        LevelScene::draw();

        showPrompt = false;
        lightMapId = 1;
    }

    virtual void init() override {
        LevelScene::init();
    };

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->scale = 1.5f;
        player->setPos(vec2(150, 150));
        PlayMusicStream(SoundCache::ref()->bgMusic);
    }

private:
    bool showPrompt = false;
};

#endif