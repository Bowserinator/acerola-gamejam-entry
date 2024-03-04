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
        news = News::random();
        scene.addChild(new StreamSite(vec2(100, 150), vec2(screenWidth - 200, screenHeight - 200), news));

        scene.addChild(new ui::Label(
            vec2(0, 40),
            vec2(screenWidth, 40),
            "Streaming... answer the questions correctly!",
            Style { .horizontalAlign = Style::Align::Left, .verticalAlign = Style::Align::Center }
        ));

        // bowser_util::setShaderValue(NewsImageCache::ref()->screenShader,
        //     NewsImageCache::ref()->screenShaderResolutionLocation, 
        //     Vector2{(float)screenWidth, (float)screenHeight});
    }

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
    }

    virtual void draw() override {
        DrawTexturePro(NewsImageCache::ref()->desktopBackground,
            Rectangle{0, 0, (float)NewsImageCache::ref()->desktopBackground.width, (float)NewsImageCache::ref()->desktopBackground.height },
            Rectangle{0, 0, (float)screenWidth, (float)screenHeight},
            Vector2{0, 0}, 0.0, WHITE);
        LevelScene::draw();
    }

private:
    News news;
};

#endif
