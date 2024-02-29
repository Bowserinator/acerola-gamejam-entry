#include "FontCache.h"
#include "raylib.h"

FontCache * FontCache::single = nullptr;

void FontCache::init() {
    if (_init) return;

    main_font = LoadFontEx("resources/joystix monospace.otf", 24.0, 0, 250);
    _init = true;
}

FontCache::~FontCache() {
    UnloadFont(main_font);
}
