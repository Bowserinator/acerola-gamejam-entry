#include "LevelSceneManager.h"
#include "scenes/scene0.h"
#include "scenes/scene1.h"
#include "scenes/scene_apt1.h"
#include "scenes/scene_apt2.h"
#include "scenes/scene_apt3.h"
#include "scenes/scene_time_test.h"
#include "scenes/memory1.h"
#include "scenes/memory2.h"
#include "scenes/memory3.h"
#include "scenes/introscene.h"
#include "scenes/gameover1.h"

LevelSceneManager::LevelSceneManager() {
    scenes.push_back(new Scene0(&player));
    scenes.push_back(new Scene1(&player));
    scenes.push_back(new SceneTimeTest(&player));
    scenes.push_back(new SceneMemory1(&player)); // 3
    scenes.push_back(new SceneMemory2(&player)); // 4
    scenes.push_back(new SceneApt1(&player)); // 5
    scenes.push_back(new SceneApt2(&player)); // 6
    scenes.push_back(new SceneApt3(&player)); // 7
    scenes.push_back(new SceneMemory3(&player)); // 8
    scenes.push_back(new IntroScene(&player)); // 9
    scenes.push_back(new GameoverScene1(&player)); // 10
}

LevelSceneManager::~LevelSceneManager() {
    for (auto i : scenes)
        delete i;
}

void LevelSceneManager::init() {
    for (auto scene : scenes) {
        scene->parent = this;
        scene->init();
    }
}

void LevelSceneManager::tick(float dt) {
    scenes[currentScene]->tick(dt);
}

void LevelSceneManager::draw() {
    scenes[currentScene]->draw();
}

void LevelSceneManager::switchScene(const std::size_t currentScene) {
    this->currentScene = currentScene;
    scenes[currentScene]->onSwitchTo();
}
