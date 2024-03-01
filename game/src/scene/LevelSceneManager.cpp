#include "LevelSceneManager.h"
#include "scenes/scene0.h"
#include "scenes/scene1.h"

LevelSceneManager::LevelSceneManager() {
    scenes.push_back(new Scene0(&player));
    scenes.push_back(new Scene1(&player));
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
