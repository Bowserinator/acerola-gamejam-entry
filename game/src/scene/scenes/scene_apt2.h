#ifndef SCENE_APT2_H
#define SCENE_APT2_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsImages.h"
#include "../../memory/News.h"

class Player;

class SceneApt2: public LevelScene {
public:
    SceneApt2(Player * player): LevelScene(player) {
        camera.zoom = 2.5;
        camera.offset = vec2(0, 20);
        
        const std::string NOTE_TITLE = "Note";

        dialogManager.addNode(DialogManager::Node(1, 121, "These streams are so depressing... not even chat is enabled.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(121, 2, "Huh... were these files always here.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 100, "It's more notes... which one should I open?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(100, 0, "")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR)
            .addChoice("SCHEDULE.txt", 3)
            .addChoice("README (2).txt", 6)
            .addChoice("Memorize the news (starts game)", 9));

        // README.txt
        dialogManager.addNode(DialogManager::Node(3, 4, "You read over the note. It's about Cassandra's monthly streaming routine.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 5, "Apparently she's only been streaming for 2 months, not counting a debut collaboration event.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(5, 100, "I remember I tried searching for news about the event, but it was very inconsistent... almost like time is unstable.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
    
        // README2.txt
        dialogManager.addNode(DialogManager::Node(6, 7, "This note is from yourself. First, apparently files randomly get deleted over time, or perhaps they simply unexist.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "Furthermore, you learn your condition is called \"the oracle's curse\", which must have been transferred to you by someone.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 100, "An oracle's old family home burned down recently; it seems you might be able to find some information there.")
            .setTitle(NOTE_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

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
        EndMode2D();
        
        LevelScene::draw();

        showPrompt = false;
    }

    virtual void init() override {
        LevelScene::init();
    };

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->scale = 1.5f;
        player->setPos(vec2(150, 150));
        hard_mode = true;
        PlayMusicStream(SoundCache::ref()->bgMusic);
    }

private:
    bool showPrompt = false;
};

#endif