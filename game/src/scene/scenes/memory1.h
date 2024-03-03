#ifndef MEMORY1_H
#define MEMORY1_H

#include "raylib.h"
#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/NewsSite.h"
#include "../../memory/News.h"
#include "../../memory/NewsImages.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"
#include "../../utils/graphics.h"

class Player;

constexpr double TIME_GIVEN = 60.0;

class SceneMemory1: public LevelScene {
public:
    SceneMemory1(Player * player): LevelScene(player) {
        player->setPos(vec2(150, screenHeight));
    }

    virtual void init() override {
        LevelScene::init();
        news = News::random();
        tex = LoadRenderTexture(screenWidth, screenHeight);
        scene.addChild(new NewsSite(vec2(100, 150), vec2(screenWidth - 200, screenHeight - 200), news));
        scene.addChild(new ui::Label(
            vec2(0, 40),
            vec2(screenWidth, 40),
            "Memorize as much as you can! You will be quizzed! (X to end early)",
            Style { .horizontalAlign = Style::Align::Left, .verticalAlign = Style::Align::Center }
        ));

        bowser_util::setShaderValue(NewsImageCache::ref()->screenShader,
            NewsImageCache::ref()->screenShaderResolutionLocation, 
            Vector2{(float)screenWidth, (float)screenHeight});
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        startTime = GetTime();
    }

    virtual void draw() override {
        BeginTextureMode(tex);
            DrawTexturePro(NewsImageCache::ref()->desktopBackground,
                Rectangle{0, 0, (float)NewsImageCache::ref()->desktopBackground.width, (float)NewsImageCache::ref()->desktopBackground.height },
                Rectangle{0, 0, (float)screenWidth, (float)screenHeight},
                Vector2{0, 0}, 0.0, WHITE);
            LevelScene::draw();

            double timeLeftPercent = 1.0 - std::min(1.0, (GetTime() - startTime) / TIME_GIVEN);
            constexpr float rHeight = 10.0f;
            DrawRectangle(screenWidth / 2, screenHeight - rHeight, screenWidth / 2 * timeLeftPercent, rHeight, WHITE);
            DrawRectangle(screenWidth / 2 * (1 - timeLeftPercent), screenHeight - rHeight, screenWidth / 2 * timeLeftPercent + 1, rHeight, WHITE);
        EndTextureMode();

        BeginShaderMode(NewsImageCache::ref()->screenShader);
            bowser_util::drawRenderTexture(tex);
        EndShaderMode();
    }

private:
    News news;
    double startTime;
    RenderTexture2D tex;
};

#endif
