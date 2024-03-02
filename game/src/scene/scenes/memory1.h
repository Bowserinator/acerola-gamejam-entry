#ifndef MEMORY1_H
#define MEMORY1_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsSite.h"
#include "../../memory/News.h"

class Player;

class SceneMemory1: public LevelScene {
public:
    SceneMemory1(Player * player): LevelScene(player) {
        player->setPos(vec2(150, screenHeight));
    }

    virtual void init() override {
        LevelScene::init();
        news = News::random();
        scene.addChild(new NewsSite(vec2(100, 100), vec2(screenWidth - 200, screenHeight - 200), news));
    }

    virtual void draw() override {

        LevelScene::draw();
    }

private:
    News news;
};

#endif
