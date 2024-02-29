#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include <vector>
#include "../config.h"
#include "../dialog/DialogBox.h"
#include "../dialog/DialogManager.h"
#include "../ui/Scene.h"

class Player;
class CollisionBox;

class LevelScene {
public:
    Player * player;
    std::vector<CollisionBox> colliders;
    ui::Scene scene;

    DialogBox * dialogBox = nullptr;
    DialogManager dialogManager;

    LevelScene(Player * player): player(player) {
        dialogBox = new DialogBox(vec2(0, screenHeight - 150), vec2(600, 150), true);
        scene.addChild(dialogBox);
        dialogManager.setBox(dialogBox);

        dialogManager.addNode(DialogManager::Node("This is an example dialog. You shouldn't read this because it's a placeholder", 1, 2));
        dialogManager.addNode(DialogManager::Node("lol 2 This is an example dialog. You shouldn't read this", 2, 0, ChoiceVector{
            std::make_pair("Go to next", 3),
            std::make_pair("Die", 4)
        }));
        dialogManager.addNode(DialogManager::Node("lol 3", 3, 1));
        dialogManager.addNode(DialogManager::Node("you died :skull:", 4, 1));
        dialogManager.jumpToNode(1);
    }

    void init();
    void tick(float dt);
    void draw();
};


#endif