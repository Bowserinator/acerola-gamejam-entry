#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "../LevelScene.h"
#include "../../config.h"
#include "../../platform/Player.h"
#include "../../utils/types/vector.h"
#include "../../ui/components/Label.h"
#include "../../ui/components/TextButton.h"
#include "../../ui/Style.h"
#include "../../memory/NewsImages.h"
#include "../../utils/graphics.h"
#include <iostream>

class TitleScene1: public LevelScene {
public:
    TitleScene1(Player * player): LevelScene(player) {
        nextScene = 0;
        camera.zoom = 1.0f;
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->setPos(vec2(0, 10000));
        animations[2].startOnce();
    }

    virtual void draw() override {
        BeginMode2D(camera);
        bowser_util::setShaderValue(shader, timeLoc, (float)GetTime());
        BeginShaderMode(shader);
        // DrawTexturePro(bg.texture, Rectangle {0, 0, 1, -1}, Rectangle{0, 0, (float)screenWidth, (float)screenHeight}, Vector2{0, 0}, 0.0f, WHITE);
        DrawTexturePro(NewsImageCache::ref()->titleBg,
            Rectangle { 0, 0, (float)NewsImageCache::ref()->titleBg.width, (float)NewsImageCache::ref()->titleBg.height },
            Rectangle { 0, 0, (float)screenWidth, (float)screenHeight },
            Vector2 {0, 0}, 0.0f, WHITE);
        EndShaderMode();
        EndMode2D();

        DrawRectangle(0, 0, 500, screenHeight, Color{0, 0, 0, 160});

        LevelScene::draw();
        DrawTexture(NewsImageCache::ref()->title, 50, 50, WHITE);
    }

    virtual void init() override {
        LevelScene::init();
        player->setPos(vec2(0, 10000));
        auto style = ui::Style {
            .horizontalAlign = ui::Style::Align::Left,
            .hoverTextColor = YELLOW
        }.setAllBorderColors(Color{0, 0, 0, 0})
         .setAllBackgroundColors(Color{0, 0, 0, 0});
        auto ys = screenHeight * 0.6f;

        shader = LoadShader(nullptr, "resources/shaders/spiral.fs");
        resLoc = GetShaderLocation(shader, "resolution");
        timeLoc = GetShaderLocation(shader, "time");

        // bg = LoadRenderTexture(1, 1);
        // BeginTextureMode(bg);
        // DrawRectangle(0, 0, 1, 1, WHITE);
        // EndTextureMode();

        bowser_util::setShaderValue(shader, resLoc, Vector2{(float)screenWidth, (float)screenHeight});

        scene.addChild((new ui::TextButton(
            vec2(50, ys),
            vec2(400, 40),
            "New game",
            style
        ))->setClickCallback([this]() {
            nextScene = 0;
            PlaySound(SoundCache::ref()->click);
            animations[1].startOnce(); // Fade out
        }));

        scene.addChild((new ui::TextButton(
            vec2(50, ys + 50),
            vec2(400, 40),
            "Skip to round 1",
            style
        ))->setClickCallback([this]() {
            nextScene = 5;
            PlaySound(SoundCache::ref()->click);
            animations[1].startOnce(); // Fade out
        }));

        scene.addChild((new ui::TextButton(
            vec2(50, ys + 2 * 50),
            vec2(400, 40),
            "Skip to round 2",
            style
        ))->setClickCallback([this]() {
            nextScene = 6;
            PlaySound(SoundCache::ref()->click);
            animations[1].startOnce(); // Fade out
        }));

        scene.addChild((new ui::TextButton(
            vec2(50, ys + 3 * 50),
            vec2(400, 40),
            "Skip to round 3",
            style
        ))->setClickCallback([this]() {
            nextScene = 7;
            PlaySound(SoundCache::ref()->click);
            animations[1].startOnce(); // Fade out
        }));

        scene.addChild((new ui::TextButton(
            vec2(50, ys + 4 * 50),
            vec2(400, 40),
            "Quit",
            style
        ))->setClickCallback([this]() {
            PlaySound(SoundCache::ref()->click);
            CloseAudioDevice();
            CloseWindow();
            std::exit(0);
        }));
    };

private:
    Shader shader;
    // RenderTexture bg;
    int timeLoc, resLoc;
};


#endif