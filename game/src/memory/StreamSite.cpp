#include "StreamSite.h"
#include "../ui/Style.h"
#include "../ui/components/HR.h"
#include "../ui/components/Label.h"
#include "../ui/components/TextButton.h"
#include "../event/FontCache.h"
#include "../utils/text_wrap.h"
#include "../utils/types/vector.h"
#include "../config.h"
#include "NewsImages.h"

#include <random>
#include <algorithm>

using namespace bowser_util;

constexpr float SHADOW = 10.0f;

StreamSite::StreamSite(const Vector2 &pos, const Vector2 &size, const News &news): ui::ScrollPanel(pos, size),
        news(news), newsQuestions(news) {
    addChild(new ui::Label(vec2(0), vec2(size.x, 100), "lol tis is the question",
        (Style {
            .horizontalAlign = Style::Align::Center
        }).setAllBackgroundColors(Color{0, 0, 0, 0})));

    constexpr float buttonPad = 10.0f;
    constexpr Vector2 buttonSize{300, 70};
    auto makeBtn = [this, buttonSize](vec2 pos) {
        return new ui::TextButton(pos, buttonSize, "Choice 1",
        (Style {
            .horizontalAlign = Style::Align::Center
        }).setAllBackgroundColors(Color{0, 0, 0, 0}));
    };

    addChild(makeBtn(vec2(size.x / 2 - buttonSize.x - buttonPad, 100)));
    addChild(makeBtn(vec2(size.x / 2 + buttonPad, 100)));
    addChild(makeBtn(vec2(size.x / 2 - buttonSize.x - buttonPad, 100 + buttonSize.y + buttonPad)));
    addChild(makeBtn(vec2(size.x / 2 + buttonPad, 100 + buttonSize.y + buttonPad)));
}

void StreamSite::draw(const Vector2 &pos) {
    const float headerHeight = NewsImageCache::ref()->browserHeader.height;
    DrawRectangle(pos.x + SHADOW, pos.y + SHADOW - headerHeight, size.x, size.y + headerHeight, Color{0, 0, 0, 128});
    DrawRectangle(pos.x, pos.y, size.x, size.y, Color{20, 20, 20, 255});
    DrawTexture(NewsImageCache::ref()->browserHeader, pos.x, pos.y - headerHeight, WHITE);

    ui::ScrollPanel::draw(pos);
}
