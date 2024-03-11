#include "NewsImages.h"
#include "raylib.h"
#include "../config.h"

NewsImageCache * NewsImageCache::single = nullptr;

void NewsImageCache::init() {
    if (_init) return;

    auto loadImg = [](const char * src) {
        Image tmp = LoadImage(src);
        Texture tex = LoadTextureFromImage(tmp);
        UnloadImage(tmp);
        return tex;
    };

    disasterImages = loadImg("resources/img/disasters.png");
    weatherImages = loadImg("resources/img/weather.png");
    stonkImages = loadImg("resources/img/stonks.png");
    lotteryImage = loadImg("resources/img/lottery.png");

    siteTitleImage = loadImg("resources/img/site-title.png");
    browserHeader = loadImg("resources/img/window-header.png");
    desktopBackground = loadImg("resources/img/desktop.png");
    apartmentBackground = loadImg("resources/img/apartment.png");
    Xprompt = loadImg("resources/img/x-prompt.png");
    chatTexture = loadImg("resources/img/chatbox.png");
    apartmentLights = loadImg("resources/img/apartment-lights.png");
    outsideLights = loadImg("resources/img/outside-lights.png");
    interactTexture = loadImg("resources/img/interact.png");
    streamStart = loadImg("resources/img/stream-start.png");
    title = loadImg("resources/img/title.png");
    titleBg = loadImg("resources/img/title-bg.png");

    screenShader = LoadShader(nullptr, "resources/shaders/screen.fs");
    screenShaderResolutionLocation = GetShaderLocation(screenShader, "resolution");

    _init = true;
}

NewsImageCache::~NewsImageCache() {
    UnloadTexture(disasterImages);
    UnloadTexture(stonkImages);
    UnloadTexture(weatherImages);
    UnloadTexture(lotteryImage);
    UnloadTexture(siteTitleImage);
    UnloadTexture(browserHeader);
    UnloadTexture(desktopBackground);
    UnloadTexture(apartmentBackground);
    UnloadTexture(Xprompt);
    UnloadTexture(chatTexture);
    UnloadTexture(apartmentLights);
    UnloadTexture(interactTexture);
    UnloadTexture(streamStart);
    UnloadTexture(title);
    UnloadTexture(titleBg);
    UnloadShader(screenShader);
    UnloadTexture(outsideLights);
}
