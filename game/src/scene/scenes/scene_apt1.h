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

        const std::string NOTE_TITLE = "Note";

        dialogManager.addNode(DialogManager::Node(1, 2, "Wait this isn't my apartment...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 0, "No, it definitely is, but why do I remember it looking different?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.addNode(DialogManager::Node(3, 100, "There's a notepad file open already... from myself?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(100, 0, "")
            .addChoice("Open MESSAGE_FROM_SELF.txt", 4)
            .addChoice("Memorize the news (Starts game)", 16));
        dialogManager.addNode(DialogManager::Node(4, 5, "Dear future (subjective past) me, in case you haven't figured it out you are experiencing time backwards.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(5, 6, "More specifically, you can only remember events from the future, as far as my tests have shown.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(6, 7, "I don't remember who Cassandra is, but I found another note from someone with her streaming account. Apparently she ran future prediction streams.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "She would memorize as much news as possible the month (after) and recite the predictions. Her account is regarded a famous clairvoyant.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 9, "Now that sounds awfully similar to our present situation, but I can't find anything about her from more than a few months back.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(9, 10, "Anyways, it seems I get stuck in a time loop until I ensure the streams go smoothly.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(10, 11, "Since you can't keep notes backwards in time you will have to rely on your memory. I tried writing down what I remembered but the notes always get mysteriously deleted...")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(11, 12, "Anyways I also wrote you some tips on using a time-reversed computer, in some ways it's very convenient.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(12, 13, "The account credentials are saved in the PC, good luck.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(13, 14, "...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
         dialogManager.addNode(DialogManager::Node(14, 15, "This is a lot to take in...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(15, 100, "I suppose I should check the news...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(16, 0, "")
            .setOnActive([this](DialogManager::Node&) {
                StopMusicStream(SoundCache::ref()->bgMusic);
                animations[1].startOnce(); // Fade out
            }));

        dialogManager.addNode(DialogManager::Node(200, 0, "No matter how hard you try, jumping from ground level to the 4th floor is impossible.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        colliders.emplace_back(0, 150, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        colliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);
        interactiveColliders.emplace_back(screenWidth / 2 / camera.zoom, 0, 100, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            showPrompt = true;
            if (IsKeyPressed(KEY_X) && dialogBox->getHidden())
                dialogManager.jumpToNode(3);
        };

        interactiveColliders.emplace_back(screenWidth * 0.8f / camera.zoom, 0, 70, screenHeight);
        interactiveColliders[1].onCollide = [this](const CollisionBox&) {
            showPrompt2 = true;
            if (IsKeyPressed(KEY_X) && dialogBox->getHidden())
                dialogManager.jumpToNode(200);
        };

        nextScene = 3;
        lightMapId = 1;
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
        if (showPrompt2)
            DrawTextureEx(
                    NewsImageCache::ref()->interactTexture,
                    Vector2{ screenWidth * 0.85f / camera.zoom - 10, 100 },
                    0.0, 0.8f / camera.zoom, WHITE
                );
        EndMode2D();
        
        LevelScene::draw();

        showPrompt = false;
        showPrompt2 = false;
    }

    virtual void init() override {
        LevelScene::init();
    };

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->scale = 1.5f;
        dialogManager.jumpToNode(1);

        player->setPos(vec2(150, 150));
        hard_mode = false;
        PlayMusicStream(SoundCache::ref()->bgMusic);
    }
private:
    bool showPrompt = false;
    bool showPrompt2 = false;
};

#endif