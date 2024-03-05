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
        player->setPos(vec2(150, 150));

        const std::string NOTE_TITLE = "Note";

        dialogManager.addNode(DialogManager::Node(1, 2, "Uhh... I can never get used to time reversed eating")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 6, "Let's see if I wrote anything to myself...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.addNode(DialogManager::Node(6, 7, "Hey so you've reached the debut stream, where she became famous")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "This is all long term predictions so there's no way that she would know unless she lived to over a hundred")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 11, "The important part is to be consistent with your answers. Good luck!")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(11, 0, "")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR)
            .addChoice("Begin final round", 9));

        dialogManager.addNode(DialogManager::Node(9, 0, "")
            .setOnActive([this](DialogManager::Node&){
                animations[1].startOnce(); // Fade out
            }));

        colliders.emplace_back(0, 190, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        colliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);
        interactiveColliders.emplace_back(screenWidth / 2 / camera.zoom, 0, 100, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            showPrompt = true;
            if (IsKeyPressed(KEY_X))
                dialogManager.jumpToNode(1);
        };

        nextScene = 3;
    }

    virtual void draw() override {
        BeginMode2D(camera);
        DrawTexture(NewsImageCache::ref()->apartmentBackground, 0, 10, WHITE);
        if (showPrompt)
            DrawTextureEx(
                NewsImageCache::ref()->Xprompt,
                Vector2{ screenWidth / 2 / camera.zoom - 10, 90 },
                0.0, 0.8f / camera.zoom, WHITE
            );
        EndMode2D();
        
        LevelScene::draw();

        showPrompt = false;
    }

    virtual void init() {
        LevelScene::init();
    };

private:
    bool showPrompt = false;
};

#endif