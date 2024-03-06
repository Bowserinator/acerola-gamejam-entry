#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include <vector>
#include "../config.h"
#include "../event/Animation.h"
#include "../dialog/DialogBox.h"
#include "../dialog/DialogManager.h"
#include "../ui/Scene.h"
#include "../utils/easing.h"
#include "../utils/camera_extra.h"

class Player;
class CollisionBox;
class LevelSceneManager;

class LevelScene {
public:
    Player * player;
    std::vector<CollisionBox> colliders;
    std::vector<CollisionBox> interactiveColliders;
    std::vector<Animation> animations;

    ui::Scene scene;
    bowser_util::Camera2DExtended camera;

    DialogBox * dialogBox = nullptr;
    DialogManager dialogManager;
    LevelSceneManager * parent = nullptr;
    std::size_t nextScene = -1;

    int lightMapId = 0;
    inline static Shader playerLightShader;
    inline static int lightTextureLoc;
    inline static int lightTextureRectLoc;

    LevelScene(Player * player): player(player) {
        dialogBox = new DialogBox(vec2(20, screenHeight - 120), vec2(screenWidth - 40, 150), true);
        dialogBox->hide();
        scene.addChild(dialogBox);
        dialogManager.setBox(dialogBox);

        Animation fadeInAnimation = Animation(0.5f);
        fadeInAnimation.easingFunction = bowser_util::easeOutBack;
        Animation fadeOutAnimation = Animation(0.5f);
        fadeOutAnimation.easingFunction = bowser_util::easeInBack;
        animations.push_back(fadeInAnimation);
        animations.push_back(fadeOutAnimation);
    }

    virtual void init();
    virtual void onSwitchTo();
    virtual void tick(float dt);
    virtual void draw();
};


#endif