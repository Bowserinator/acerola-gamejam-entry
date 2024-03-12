#ifndef END_SCENE1
#define END_SCENE1


#include "../LevelScene.h"
#include "../../config.h"
#include "../../platform/Player.h"

class EndScene1: public LevelScene {
public:
    EndScene1(Player * player): LevelScene(player) {
        camera.zoom = 2.5;
        camera.offset = vec2(0, 20);
        player->setPos(vec2(150, 150));

        const std::string NPCTitle = "Receptionist";

        dialogManager.addNode(DialogManager::Node(1, 2, "It has been several years since I started remembering backwards in time.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(2, 3, "Unfortunately, knowledge of the future hasn't helped me win the lottery")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(3, 4, "But it's nice knowing no matter what I do I can't die or get seriously injured.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(4, 5, "...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(5, 6, "I actually bumped into Cassandra the other day. I told her she was going to end up in an accident in several years.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(6, 7, "She told me not to worry about it, and that I would forget about the future by yesterday.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(7, 8, "Supposedly, I once told her the same thing... not sure why I was able to remember her then.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(8, 9, "Kind of funny, we could be trapped in a time loop of our own making, an inescapable local extrema of entropy.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(9, 10, "Only a hypothesis of course, I would have no way of knowing, and frankly it doesn't quite matter.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(10, 11, "I do wish we could've spend some more time together... she told me yesterday was the first time we met.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(11, 12, "...")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(12, 13, "The eastern sunset is beautiful. I'm going to miss it.")
            .setTitle(PLAYER_TITLE).setTitleColor(PLAYER_TITLE_COLOR));
        dialogManager.addNode(DialogManager::Node(13, 0, "")
            .setOnActive([this](DialogManager::Node &) { animations[2].startOnce(); }));

        colliders.emplace_back(0, 170, screenWidth, 100);
        colliders.emplace_back(-100, 0, 100, screenHeight);
        nextScene = 1;
    }

    virtual void draw() override {
        UpdateMusicStream(SoundCache::ref()->endMusic);
        player->setPos(vec2(150, screenHeight));
        player->velocity = vec2(0);

        if (!start && animations[0].progress() == 1.0f) {
            dialogManager.jumpToNode(1);
            start = true;
        }


        BeginMode2D(camera);
        DrawTexturePro(bg,
            Rectangle{0, 0, (float)bg.width, (float)bg.height },
            Rectangle{0, 10, (float)screenWidth / camera.zoom, (float)bg.height },
            Vector2{0, 0}, 0.0f, WHITE);
        EndMode2D();

        LevelScene::draw();

        if (animations[2].progress() == 1.0f)
            animations[3].startOnce();

        if (animations[3].progress()) {
            DrawTexturePro(thankBg,
                Rectangle{0, 0, (float)thankBg.width, (float)thankBg.height },
                Rectangle{0, 0, (float)screenWidth, (float)screenHeight * 0.8f },
                Vector2{0, -70}, 0.0f,
                Color { 255, 255, 255, (unsigned char)(animations[3].progress() * 255) });
        }
        if (animations[3].progress() > 0.5f) {
            if (IsKeyPressed(KEY_X)) {
                nextScene = 13; // title screen
                animations[1].startOnce(); // Fade out
                StopMusicStream(SoundCache::ref()->endMusic);
            }
        }
    }

    virtual void init() override {
        LevelScene::init();
        animations[0].setDuration(4.0f);
        animations.push_back(Animation(2.0f));
        animations.push_back(Animation(5.0f));

        Image bgImg = LoadImage("resources/img/end1.png");
        Image tImg = LoadImage("resources/img/thank-you.png");
        bg = LoadTextureFromImage(bgImg);
        thankBg = LoadTextureFromImage(tImg);
        UnloadImage(bgImg);
        UnloadImage(tImg);
    };

    virtual void onSwitchTo() override {
        LevelScene::onSwitchTo();
        player->scale = 1.3f;
        PlayMusicStream(SoundCache::ref()->endMusic);
        start = false;
        dialogManager.jumpToNode(0);
    }

private:
    Texture2D bg, thankBg;
    bool start = false;
};


#endif