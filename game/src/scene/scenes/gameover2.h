#ifndef GAME_OVER_SCENE2_H
#define GAME_OVER_SCENE2_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../platform/Player.h"
#include "../../utils/types/vector.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"
#include "../../memory/News.h"

class GameoverScene2: public LevelScene {
public:
    GameoverScene2(Player * player): LevelScene(player) {
        nextScene = 0;
        camera.zoom = 1.0f;
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->setPos(vec2(0, 10000));
        animations[2].startOnce();
    }

    virtual void draw() override {
        LevelScene::draw();

        if (animations[2].progress() == 1.0f)
            animations[3].startOnce();
        if (animations[3].progress() == 1.0f)
            animations[4].startOnce();

        label1->style.textColor.a = (unsigned char)(animations[2].progress() * 255);
        label2->style.textColor.a = (unsigned char)(animations[3].progress() * 255);

        if (IsKeyPressed(KEY_X)) {
            nextScene = hard_mode ? 6 : 5;
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
            "As you blurt out the words, time seems to reset...",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(RED)
        );
        label2 = new ui::Label(
            vec2(0, screenHeight * 0.8),
            vec2(screenWidth, 40),
            "You answered incorrectly. Press X to restart",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );

        scene.addChild(label1);
        scene.addChild(label2);
    };

private:
    ui::Label * label1, * label2;
};


#endif