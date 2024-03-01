#ifndef SCENE0_H
#define SCENE0_H

#include "../LevelScene.h"
#include "../../config.h"

class Player;

class Scene0: public LevelScene {
public:
    Scene0(Player * player): LevelScene(player) {
        camera.zoom = 2.5;
        camera.offset = vec2(0, 20);
        player->setPos(vec2(150, 150));

        const std::string NPCTitle = "Receptionist";

        dialogManager.addNode(DialogManager::Node(1, 2, "I didn't? Anyways it's down the hall to the right")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(2, 3, "How did you know what I was going to ask?")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(3, 4, "Nevermind...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 5, "Hmm?")
            .setTitle(NPCTitle).setTitleColor(NPC1_TITLE_COLOR).setBackwards());
        dialogManager.addNode(DialogManager::Node(5, 0, "I was going to ask where the exit is, forget it")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.jumpToNode(1);

        colliders.emplace_back(0, 190, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        interactiveColliders.emplace_back(screenWidth / camera.zoom, 0, 100, screenHeight);
        interactiveColliders[0].onCollide = [this](const CollisionBox&) {
            animations[1].startOnce(); // Fade out
        };

        nextScene = 1;
    }

    virtual void draw() override {
        BeginMode2D(camera);
        DrawTexture(bg, 0, 10, WHITE);
        EndMode2D();
        
        LevelScene::draw();
    }

    virtual void init() {
        LevelScene::init();
        Image bgImg = LoadImage("resources/img/scene0-1.png");
        bg = LoadTextureFromImage(bgImg);
        UnloadImage(bgImg);
    };

private:
    Texture2D bg;
};

#endif