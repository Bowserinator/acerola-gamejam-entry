#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include <vector>
#include "../config.h"
#include "../dialog/DialogBox.h"

class Player;
class CollisionBox;

class LevelScene {
public:
    Player * player;
    std::vector<CollisionBox> colliders;
    DialogBox dialogBox = DialogBox(vec2(0, screenHeight - 150), vec2(300, 150), true).setText("This text should be longer than a single line");

    LevelScene(Player * player): player(player) {}

    void init();
    void tick(float dt);
    void draw();
};


#endif