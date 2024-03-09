#ifndef GAME_OVER_SCENE2_H
#define GAME_OVER_SCENE2_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../platform/Player.h"
#include "../../utils/types/vector.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"
#include "../../memory/News.h"

#include <string>

inline std::string GAMEOVER_REASON2;

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
        label2->setText(GAMEOVER_REASON2);
    }

    virtual void draw() override {
        LevelScene::draw();

        if (animations[2].progress() == 1.0f)
            animations[3].startOnce();
        if (animations[3].progress() == 1.0f)
            animations[4].startOnce();

        label1->style.textColor.a = (unsigned char)(animations[2].progress() * 255);
        label2->style.textColor.a = (unsigned char)(animations[2].progress() * 255);
        label3->style.textColor.a = (unsigned char)(animations[3].progress() * 255);

        if (IsKeyPressed(KEY_X)) {
            nextScene = 8;
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
            vec2(0, screenHeight / 3),
            vec2(screenWidth, 40),
            "Placeholder reason",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(RED)
        );
        label3 = new ui::Label(
            vec2(0, screenHeight * 0.8),
            vec2(screenWidth, 40),
            "Press X to restart",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );

        scene.addChild(label1);
        scene.addChild(label2);
        scene.addChild(label3);
    };

private:
    ui::Label * label1, * label2, * label3;
};


#endif