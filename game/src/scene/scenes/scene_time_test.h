#ifndef SCENE_TIME_TEST_H
#define SCENE_TIME_TEST_H

#include "../../platform/Player.h"
#include "../TimeLevelScene.h"
#include "../../config.h"
#include "../level/debris.h"
#include "../../utils/easing.h"
#include "../../memory/News.h"

class Player;

class SceneTimeTest: public TimeLevelScene {
public:
    SceneTimeTest(Player * player): TimeLevelScene(player) {
        camera.zoom = 4;
        player->setPos(vec2(150, 150));

        nextScene = 1;
        colliders.emplace_back(0, 200, 300, 10);

        debris.push_back(Debris {
           // std::function<void(LevelScene*)> onComplete = [](LevelScene*) {};
            .startRotation = 270.3f,
            .targetRotation = 0.0f,
            .startPos = vec2(100, 300),
            .targetPos = vec2(0, 0),
            .moveAnimation = Animation(1.0f).setEasingFunction([](float x) { return bowser_util::easeOutCubic(x); })
        });
        debris.push_back(Debris {
           // std::function<void(LevelScene*)> onComplete = [](LevelScene*) {};
            .startRotation = 160.3f,
            .targetRotation = 0.0f,
            .startPos = vec2(150, 300),
            .targetPos = vec2(0, 64),
            .moveAnimation = Animation(1.2f).setEasingFunction([](float x) { return bowser_util::easeOutCubic(x); })
        });
        debris.push_back(Debris {
            // std::function<void(LevelScene*)> onComplete = [](LevelScene*) {};
            .startRotation = 160.3f,
            .targetRotation = 0.0f,
            .startPos = vec2(150, 360),
            .targetPos = vec2(0, 32),
            .moveAnimation = Animation(1.5f).setEasingFunction([](float x) { return bowser_util::easeOutCubic(x); })
        });
    }


    virtual void tick(float dt) override {
        TimeLevelScene::tick(dt);

        if (IsKeyPressed(KEY_P)) {
            for (auto &d : debris)
                d.moveAnimation.startOnce();
            News::random();
        }

        for (auto &d : debris)
            d.tick(dt);
    }

    virtual void draw() override {
        TimeLevelScene::draw();
        for (auto &d : debris)
            d.draw();
    }

    virtual void init() override {
        TimeLevelScene::init();
    };

private:
    std::vector<Debris> debris;
};

#endif