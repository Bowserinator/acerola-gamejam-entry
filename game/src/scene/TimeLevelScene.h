#ifndef TIME_LEVEL_SCENE_H
#define TIME_LEVEL_SCENE_H

#include "./LevelScene.h"
#include "../config.h"
#include <vector>

class Player;

constexpr int MAX_STATES = 60 * 60 * 60; // 1 Hour of states = 216k * bytes in struct

class TimeLevelScene: public LevelScene {
public:
    TimeLevelScene(Player * player): LevelScene(player) {
        
    }

    virtual void restart();
    virtual void tick(float dt) override;
    virtual void draw() override;
private:
    struct State {
        float playerX;
        float playerY;
    };

    bool reversingTime = false;
    std::vector<State> states;
};

#endif