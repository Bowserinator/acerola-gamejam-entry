#include "FontCache.h"
#include "raylib.h"
#include "../config.h"

FontCache * FontCache::single = nullptr;

void FontCache::init() {
    if (_init) return;

    web = LoadFontEx("resources/dogicapixel.ttf", FONT_SIZE, 0, 250);
    main_font = LoadFontEx("resources/joystix monospace.otf", FONT_SIZE, 0, 250);
    _init = true;
}

FontCache::~FontCache() {
    UnloadFont(main_font);
    UnloadFont(web);
}
