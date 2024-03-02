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

    _init = true;
}

NewsImageCache::~NewsImageCache() {
    UnloadTexture(disasterImages);
    UnloadTexture(stonkImages);
    UnloadTexture(weatherImages);
    UnloadTexture(lotteryImage);
    UnloadTexture(siteTitleImage);
}