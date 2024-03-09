#ifndef MEMORY2_H
#define MEMORY2_H

#include "raylib.h"
#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/StreamSite.h"
#include "../../memory/News.h"
#include "../../memory/NewsImages.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"
#include "../../utils/graphics.h"

class Player;

class SceneMemory2: public LevelScene {
public:
    SceneMemory2(Player * player): LevelScene(player) {
        player->setPos(vec2(150, screenHeight));
    }

    virtual void init() override {
        LevelScene::init();
        news = global_news;
        screenShader = LoadShader(nullptr, "resources/shaders/wrong.fs");
        shaderStrengthLoc = GetShaderLocation(screenShader, "strength");
        tex = LoadRenderTexture(screenWidth, screenHeight);
        SetTextureWrap(tex.texture, TEXTURE_WRAP_CLAMP);

        site = new StreamSite(vec2(100, 150), vec2(screenWidth - 200, screenHeight - 200), news);
        scene.addChild(site);

        scene.addChild(new ui::Label(
            vec2(0, 40),
            vec2(screenWidth, 40),
            "Streaming... answer the questions correctly!",
            Style { .horizontalAlign = Style::Align::Left, .verticalAlign = Style::Align::Center }
        ));

        bowser_util::setShaderValue(screenShader,
            GetShaderLocation(screenShader, "resolution"), 
            Vector2{(float)screenWidth, (float)screenHeight});
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        site->reset();
        player->setPos(vec2(150, screenHeight));
    }

    virtual void draw() override {
        LevelScene::draw();
        if (site->incorrectTotal >= 3) {
            nextScene = 10;
            animations[1].startOnce(); // Fade out
        }
        else if (site->done && GetTime() - site->endTime > 5.0f) {
            nextScene = hard_mode ? 7 : 6;
            animations[1].startOnce(); // Fade out
        }

        BeginTextureMode(tex);
            DrawTexturePro(NewsImageCache::ref()->desktopBackground,
                Rectangle{0, 0, (float)NewsImageCache::ref()->desktopBackground.width, (float)NewsImageCache::ref()->desktopBackground.height },
                Rectangle{0, 0, (float)screenWidth, (float)screenHeight},
                Vector2{0, 0}, 0.0, WHITE);
            LevelScene::draw();
        EndTextureMode();

        bowser_util::setShaderValue(screenShader, shaderStrengthLoc, site->distortion); 

        BeginShaderMode(screenShader);
            bowser_util::drawRenderTexture(tex);
        EndShaderMode();
    }

private:
    News news;
    Shader screenShader;
    StreamSite * site;
    RenderTexture2D tex;
    int shaderStrengthLoc;
};

#endif
