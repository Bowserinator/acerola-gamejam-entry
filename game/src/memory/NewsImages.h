#ifndef NEWS_IMAGES_H
#define NEWS_IMAGES_H

#include "raylib.h"

class NewsImageCache {
public:
    Texture disasterImages;
    Texture weatherImages;
    Texture stonkImages;
    Texture lotteryImage;

    Texture siteTitleImage;
    Texture browserHeader;
    Texture desktopBackground;

    Texture apartmentBackground;
    Texture Xprompt;

    Shader screenShader;
    int screenShaderResolutionLocation;

    NewsImageCache(NewsImageCache &other) = delete;
    void operator=(const NewsImageCache&) = delete;
    ~NewsImageCache();

    // Call after OpenGL context has been initialized
    void init();

    static NewsImageCache * ref() {
        if (single == nullptr) [[unlikely]]
            single = new NewsImageCache;
        return single;
    };

    static void destroy() {
        delete single;
        single = nullptr;
    }
private:
    bool _init;
    static NewsImageCache * single;

    NewsImageCache(): _init(false) {}
};

#endif