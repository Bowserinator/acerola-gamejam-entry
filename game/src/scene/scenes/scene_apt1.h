#ifndef SCENE_APT1_H
#define SCENE_APT1_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsImages.h"
#include "../../memory/News.h"

class Player;

class SceneApt1: public LevelScene {
public:
    SceneApt1(Player * player): LevelScene(player) {
        camera.zoom = 2.5;
        camera.offset = vec2(0, 20);
        player->setPos(vec2(150, 150));

        hard_mode = false;

        const std::string NOTE_TITLE = "Note";

        dialogManager.addNode(DialogManager::Node(1, 2, "What is going on?....")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 3, "Is this a note... it's from myself?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(3, 4, "Dear future? self if you haven't figured it out yet you can only remember the future")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 5, "I have no idea why this is happening but it might be related to Cassandra")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(5, 6, "Somehow we ended up in her role")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(6, 7, "Apparently she did a monthly 'future predictions' stream")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "She would memorize as much news as possible the month before (after?)")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 9, "We need to make sure those streams happen to preserve the timeline")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(9, 10, "Since you can't keep notes backwards in time you will have to rely on your memory")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(10, 11, "I tried writing down what I remembered but the notes got lost")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(11, 12, "Maybe they got erased from the timeline entirely...")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(12, 13, "The account credentials are saved in the PC, good luck")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(13, 14, "...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
         dialogManager.addNode(DialogManager::Node(14, 15, "This is a lot to take in...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(15, 0, "I suppose I should check out the PC...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.jumpToNode(1);

        colliders.emplace_back(0, 190, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        colliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);
        interactiveColliders.emplace_back(screenWidth / 2 / camera.zoom, 0, 100, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            showPrompt = true;
            if (IsKeyPressed(KEY_X))
                animations[1].startOnce(); // Fade out
        };

        nextScene = 3;
        lightMapId = 1;
    }

    virtual void draw() override {
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
    }

    virtual void init() {
        LevelScene::init();
    };

private:
    bool showPrompt = false;
};

#endif