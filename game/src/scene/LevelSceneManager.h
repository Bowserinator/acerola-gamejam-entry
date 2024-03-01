#ifndef LEVEL_SCENE_MANAGER_H
#define LEVEL_SCENE_MANAGER_H

#include <vector>
#include "LevelScene.h"
#include "../platform/Player.h"

class LevelSceneManager {
public:
    LevelSceneManager();

    void init();
    void tick(float dt);
    void draw();
    void switchScene(const std::size_t currentScene);
private:
    std::vector<LevelScene*> scenes;
    std::size_t currentScene = 0;
    Player player;
};

#endif