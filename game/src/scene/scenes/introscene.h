#ifndef INTRO_SCENE_H
#define INTRO_SCENE_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../platform/Player.h"
#include "../../utils/types/vector.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"

class IntroScene: public LevelScene {
public:
    IntroScene(Player * player): LevelScene(player) {
        nextScene = 0;
        camera.zoom = 1.0f;
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->setPos(vec2(0, 10000));
    }

    virtual void draw() override {
        LevelScene::draw();

        if (animations[2].progress() == 1.0f)
            animations[3].startOnce();
        if (animations[3].progress() == 1.0f)
            animations[4].startOnce();
        if (animations[4].progress() == 1.0f)
            animations[5].startOnce();
        if (animations[5].progress() == 1.0f)
            animations[6].startOnce();

        label1->style.textColor.a = (unsigned char)(animations[2].progress() * 255);
        label2->style.textColor.a = (unsigned char)(animations[3].progress() * 255);
        label3->style.textColor.a = (unsigned char)(animations[4].progress() * 255);
        label4->style.textColor.a = (unsigned char)(animations[5].progress() * 255);
        label5->style.textColor.a = (unsigned char)(animations[6].progress() * 255);

        if (IsKeyPressed(KEY_X))
            animations[1].startOnce(); // Fade out
    }

    virtual void init() {
        LevelScene::init();
        player->setPos(vec2(0, 10000));

        animations.push_back(Animation(1.5f));
        animations.push_back(Animation(3.5f));
        animations.push_back(Animation(1.5f));
        animations.push_back(Animation(1.5f));
        animations.push_back(Animation(1.5f));
        animations[2].startOnce();

        label1 = new ui::Label(
            vec2(0, screenHeight / 3 - 40),
            vec2(screenWidth, 40),
            "Her last words to me were",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );
        label2 = new ui::Label(
            vec2(0, screenHeight / 3),
            vec2(screenWidth, 40),
            "'I may not remember who you are, but this is the last time we'll meet'",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(RED)
        );
        label3 = new ui::Label(
            vec2(0, screenHeight / 3 + 40 * 2),
            vec2(screenWidth, 40),
            "Cassandra... why can't I remember who she is",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );
        label4 = new ui::Label(
            vec2(0, screenHeight / 3 + 40 * 2.7f),
            vec2(screenWidth, 40),
            "Why... can't I remember anything...",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );
        label5 = new ui::Label(
            vec2(0, screenHeight * 0.8),
            vec2(screenWidth, 40),
            "Press X to continue",
            (ui::Style { .horizontalAlign = Style::Align::Center })
                .setAllTextColors(WHITE)
        );

        scene.addChild(label1);
        scene.addChild(label2);
        scene.addChild(label3);
        scene.addChild(label4);
        scene.addChild(label5);
    };

private:
    ui::Label * label1, * label2, * label3, * label4, * label5;
};

#endif
