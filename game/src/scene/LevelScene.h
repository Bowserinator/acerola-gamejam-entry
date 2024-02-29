#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include <vector>
#include "../config.h"
#include "../dialog/DialogBox.h"
#include "../ui/Scene.h"

class Player;
class CollisionBox;

class LevelScene {
public:
    Player * player;
    std::vector<CollisionBox> colliders;
    ui::Scene scene;

    DialogBox * dialogBox = nullptr;

    LevelScene(Player * player): player(player) {
        dialogBox = new DialogBox(vec2(0, screenHeight - 150), vec2(300, 150), true);
        scene.addChild(dialogBox);
    }

    void init();
    void tick(float dt);
    void draw();
};


#endif