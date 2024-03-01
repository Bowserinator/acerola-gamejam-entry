#ifndef SCENE1_H
#define SCENE1_H

#include "../LevelScene.h"
#include "../../config.h"

class Player;

class Scene1: public LevelScene {
public:
    Scene1(Player * player): LevelScene(player) {
        camera.zoom = 1.5;

        const std::string NPCTitle = "Taxi Driver";

        dialogManager.addNode(DialogManager::Node(1, 2, "*I think I know what's going on*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 3, "*I have to get back to that store...*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(3, 4, "*Damn it's not on my phone... what was the address again?*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 5, "*Oh right, I had this sticky note in my pocket*")
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
        dialogManager.addNode(DialogManager::Node(11, 0, "*The driver hands me a wad of cash and leaves*")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.jumpToNode(1);
    }
};

#endif