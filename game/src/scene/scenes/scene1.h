#ifndef SCENE1_H
#define SCENE1_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsImages.h"

class Player;

class Scene1: public LevelScene {
public:
    Scene1(Player * player): LevelScene(player) {
        camera.zoom = 2.5;

        const std::string NPCTitle = "Taxi Driver";
        nextScene = 5;

        dialogManager.addNode(DialogManager::Node(1, 2, "Why was I visiting Cassandra at the hospital?...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 3, "I have to get back to my apartment...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(3, 4, "Damn it's not on my phone... what was the address again?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 100, "Oh right, I had this sticky note in my pocket")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(100, 0, "How convenient, there's a taxi there")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        dialogManager.addNode(DialogManager::Node(5, 6, "What a nutcase!")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(6, 7, "*A taxi driver! Maybe they can take me there*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "*I show the note to the driver*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 9, "Can you take me to this address?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(9, 10, "Where? We're already here!")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(10, 11, "*I took this taxi before? Maybe I shouldn't say anything...*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));

        // TODO cutscene inbetween
        dialogManager.addNode(DialogManager::Node(11, 12, "*The driver hands me a wad of cash and leaves*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(12, 0, "")
            .setOnActive([this](DialogManager::Node&) {
                animations[1].startOnce(); // Fade out
            }));
        dialogManager.jumpToNode(1);

        colliders.emplace_back(0, 195, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        colliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);

        interactiveColliders.emplace_back(screenWidth / 2 / camera.zoom, 0, 200, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            showPrompt = true;
            if (IsKeyPressed(KEY_X) && dialogBox->getHidden())
                dialogManager.jumpToNode(5);
        };

        lightMapId = 2;
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