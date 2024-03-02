#include "raylib.h"
#include "config.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "event/EventBuffer.h"
#include "event/FontCache.h"
#include "memory/NewsImages.h"

#include "platform/Player.h"
#include "scene/LevelSceneManager.h"

LevelSceneManager manager;

int main(void) {
    InitWindow(screenWidth, screenHeight, windowTitle);

    InitAudioDevice();
    NewsImageCache::ref()->init();
    FontCache::ref()->init();

    manager.init();
    manager.switchScene(3);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, FPS, 1);
#else
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        EventBuffer::ref()->reset();

        manager.tick(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        manager.draw();
        EndDrawing();
    }
#endif

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

