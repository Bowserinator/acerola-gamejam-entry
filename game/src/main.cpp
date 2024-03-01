#include "raylib.h"
#include "config.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "event/EventBuffer.h"
#include "event/FontCache.h"

#include "platform/Player.h"
#include "scene/scenes/scene0.h"
#include "scene/scenes/scene1.h"

Player p;
Scene0 scene(&p);


int main(void) {
    InitWindow(screenWidth, screenHeight, windowTitle);

    InitAudioDevice();
    FontCache::ref()->init();

    scene.init();
    scene.onSwitchTo();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, FPS, 1);
#else
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        EventBuffer::ref()->reset();

        scene.tick(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        scene.draw();
        EndDrawing();
    }
#endif

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

