#include "NewsSite.h"
#include "../ui/Style.h"
#include "../event/FontCache.h"
#include "../utils/text_wrap.h"
#include "../config.h"

constexpr float GAP = 10.0f;
constexpr float GRID_ITEM_HEIGHT = 150.0;
constexpr float IMAGE_WIDTH = 150.0;

NewsSite::NewsSite(const Vector2 &pos, const Vector2 &size, const News &news): ui::ScrollPanel(pos, size), news(news) {
    internalSize.y = 1000.0;


    // TODO: aggergated news:
    // title, subtitle, image - that is all
    // also randomize order
    // bg image: browser
}

void NewsSite::draw(const Vector2 &pos) {
    DrawRectangle(pos.x, pos.y, size.x, size.y, RAYWHITE);
    ui::ScrollPanel::draw(pos);

    const float GRID_ITEM_WIDTH = size.x - 3 * GAP;

    BeginScissorMode(pos.x, pos.y, size.x, size.y);
    for (int i = 0; i < news.stonks.size(); i++) {
        auto y = GAP + i * (GRID_ITEM_HEIGHT + GAP);
        DrawRectangleLines(pos.x + GAP, pos.y + y + offsetTop, GRID_ITEM_WIDTH, GRID_ITEM_HEIGHT, BLACK);
        bowser_util::DrawTextBoxed(
            FontCache::ref()->main_font,
            news.stonks[i].summary.c_str(),
            Rectangle {
                pos.x + GAP + IMAGE_WIDTH + GAP,
                pos.y + y + offsetTop + GAP,
                GRID_ITEM_WIDTH - IMAGE_WIDTH - 2 * GAP,
                GRID_ITEM_HEIGHT - 2 * GAP
            },
            FONT_SIZE, FONT_SPACING, true, BLACK
        );

        bowser_util::DrawTextBoxed(
            FontCache::ref()->main_font,
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
            Rectangle {
                pos.x + GAP + IMAGE_WIDTH + GAP,
                pos.y + y + offsetTop + GAP + FONT_SIZE,
                GRID_ITEM_WIDTH - IMAGE_WIDTH - 2 * GAP,
                GRID_ITEM_HEIGHT - 2 * GAP - FONT_SIZE
            },
            FONT_SIZE, FONT_SPACING, true, GRAY
        );
    }
    EndScissorMode();
}
