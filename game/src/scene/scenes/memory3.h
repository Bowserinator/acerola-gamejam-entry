#ifndef MEMORY3_H
#define MEMORY3_H

#include "raylib.h"
#include "../../platform/Player.h"
#include "../LevelScene.h"
#include "../../config.h"
#include "../../memory/StreamFestSite.h"
#include "../../memory/News.h"
#include "../../memory/NewsImages.h"
#include "../../ui/components/Label.h"
#include "../../ui/Style.h"
#include "../../utils/graphics.h"

class Player;

class SceneMemory3: public LevelScene {
public:
    SceneMemory3(Player * player): LevelScene(player) {
        player->setPos(vec2(150, screenHeight));
    }

    virtual void init() override {
        LevelScene::init();
        screenShader = LoadShader(nullptr, "resources/shaders/wrong2.fs");
        shaderStrengthLoc = GetShaderLocation(screenShader, "strength");
        tex = LoadRenderTexture(screenWidth, screenHeight);
        SetTextureWrap(tex.texture, TEXTURE_WRAP_CLAMP);

        site = new StreamFestSite(vec2(100, 150), vec2(screenWidth - 200, screenHeight - 200));
        scene.addChild(site);

        label = new ui::Label(
            vec2(0, 40),
            vec2(screenWidth, 40),
            "Streaming... answer the questions consistently!",
            Style { .horizontalAlign = Style::Align::Left, .verticalAlign = Style::Align::Center }
        );
        scene.addChild(label);

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
        if (site->incorrectTotal > 0) {
            nextScene = 12;
            animations[1].startOnce(); // Fade out
        }

        label->setText(TextFormat("Streaming... answer the questions consistently! [%d / 40]", site->question));

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
    Shader screenShader;
    StreamFestSite * site;
    RenderTexture2D tex;
    int shaderStrengthLoc;
    ui::Label * label;
};

#endif
