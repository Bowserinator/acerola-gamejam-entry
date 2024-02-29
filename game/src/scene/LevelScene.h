#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include <vector>

class Player;
class CollisionBox;

class LevelScene {
public:
    Player * player;
    std::vector<CollisionBox> colliders;

    LevelScene(Player * player): player(player) {}

    void tick(float dt);
    void draw();
};


#endif