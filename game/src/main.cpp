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

#ifdef DEBUG
#include <glad.h>

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam ) {
    if (id == 0x20071 || id == 0x20072) return; // Usage hint is GL_STATIC_READ< will use VIDEO memory as the source for buffer object operations

    fprintf(stderr, "GL CALLBACK: %s id = 0x%x, type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            id, type, severity, message);
}
#endif

int main(void) {
    InitWindow(screenWidth, screenHeight, windowTitle);

    InitAudioDevice();
    NewsImageCache::ref()->init();
    FontCache::ref()->init();

    manager.init();
    manager.switchScene(1);

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

