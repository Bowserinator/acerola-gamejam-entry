#include "raylib.h"
#include "config.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int main(void) {
    InitWindow(screenWidth, screenHeight, windowTitle);

    InitAudioDevice();


#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, FPS, 1);
#else
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }
#endif

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

