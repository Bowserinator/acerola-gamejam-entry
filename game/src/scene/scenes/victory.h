#ifndef VICTORY_H
#define VICTORY_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../platform/Player.h"
#include "../../utils/types/vector.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"
#include "../../memory/News.h"
#include "../../event/SoundCache.h"
#include "../../particle/Particle.h"

#include <string>
#include <iostream>

extern int WIN_SCORE;
extern int TOTAL_QUESTIONS;

using namespace ui;

class VictoryScene: public LevelScene {
public:
    VictoryScene(Player * player): LevelScene(player) {
        nextScene = 0;
        camera.zoom = 1.0f;
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->setPos(vec2(0, 10000));
        animations[2].startOnce();
        PlaySound(SoundCache::ref()->yay);

        parts.particles.clear();
        Color colors[] = { RED, GREEN, ORANGE, BLUE, YELLOW, PURPLE };

        for (int i = 0; i < 30; i++) {
            parts.particles.emplace_back(
                GetRandomValue(2, 5),
                colors[rand() % 6],
                vec2(10, screenHeight - 10),
                GetRandomValue(20, 40) * vec2(1, -1).rotate(GetRandomValue(-15, 15) * DEG2RAD),
                1.0f, 200.0f
            );
            parts.particles.emplace_back(
                GetRandomValue(2, 5),
                colors[rand() % 6],
                vec2(screenWidth - 10, screenHeight - 10),
                GetRandomValue(20, 40) * vec2(-1, -1).rotate(GetRandomValue(-15, 15) * DEG2RAD),
                1.0f, 200.0f
            );
        }
    }

    virtual void draw() override {
        parts.tick();
        LevelScene::draw();
        parts.draw();

        if (animations[2].progress() == 1.0f)
            animations[3].startOnce();
        if (animations[3].progress() == 1.0f)
            animations[4].startOnce();

        label2->setText(TextFormat("%d / %d answered", WIN_SCORE, TOTAL_QUESTIONS) + std::string(". Press X to go to next month..."));
        label1->style.textColor.a = (unsigned char)(animations[2].progress() * 255);
        label2->style.textColor.a = (unsigned char)(animations[3].progress() * 255);

        if (IsKeyPressed(KEY_X)) {
            nextScene = hard_mode ? 7 : 6;
            animations[1].startOnce(); // Fade out
        }
    }

    virtual void init() override {
        LevelScene::init();
        player->setPos(vec2(0, 10000));

        animations.push_back(Animation(2.0f));
        animations.push_back(Animation(2.0f));

        label1 = new ui::Label(
            vec2(0, screenHeight / 3 - 40),
            vec2(screenWidth, 40),
            "STREAM SUCCESS!",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(GREEN)
        );
        label2 = new ui::Label(
            vec2(0, screenHeight * 0.5),
            vec2(screenWidth, 40),
            TextFormat("%d / %d answered", WIN_SCORE, TOTAL_QUESTIONS) + std::string(". Press X to continue..."),
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );

        scene.addChild(label1);
        scene.addChild(label2);
    };

private:
    ui::Label * label1, * label2;
    ParticleManager parts;
};

#endif