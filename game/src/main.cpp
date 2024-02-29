#include "raylib.h"
#include "config.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "event/EventBuffer.h"
#include "event/FontCache.h"

#include "platform/Player.h"
#include "scene/LevelScene.h"

Player p;
LevelScene scene(&p);


int main(void) {
    InitWindow(screenWidth, screenHeight, windowTitle);

    InitAudioDevice();
    FontCache::ref()->init();

    scene.colliders.emplace_back(0, 300, 300, 10);
    scene.colliders.emplace_back(100, 270, 300, 10);
    scene.colliders.emplace_back(0, 250, 10, 50);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, FPS, 1);
#else
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        EventBuffer::ref()->reset();

        scene.tick(GetFrameTime());

        BeginDrawing();
        scene.draw();
        EndDrawing();
    }
#endif

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

