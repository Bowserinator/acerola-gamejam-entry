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
        dialogBox = new DialogBox(vec2(20, screenHeight - 170), vec2(screenWidth - 40, 150), true);
        scene.addChild(dialogBox);
        dialogManager.setBox(dialogBox);

        dialogManager.addNode(DialogManager::Node(1, 2, "This is an example dialog. You shouldn't read this because it's a placeholder"));
        dialogManager.addNode(DialogManager::Node(2, 0, "lol 2 This is an example dialog. You shouldn't read this")
            .addChoice("Go to next", 3)
            .addChoice("die", 4)
        );
        dialogManager.addNode(DialogManager::Node(3, 1, "lol 3"));
        dialogManager.addNode(DialogManager::Node(4, 1, "you died :skull:"));
        dialogManager.jumpToNode(1);
    }

    void init();
    void tick(float dt);
    void draw();
};


#endif