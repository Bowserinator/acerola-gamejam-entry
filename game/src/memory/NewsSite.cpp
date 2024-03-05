#include "NewsSite.h"
#include "../ui/Style.h"
#include "../ui/components/HR.h"
#include "../event/FontCache.h"
#include "../utils/text_wrap.h"
#include "../utils/types/vector.h"
#include "../config.h"
#include "NewsImages.h"

#include <random>
#include <algorithm>

using namespace bowser_util;

constexpr float GAP = 15.0f;
constexpr float GRID_ITEM_HEIGHT = 80.0f;
constexpr float IMAGE_WIDTH = 70.0f;
constexpr float IMAGE_HEIGHT = 70.0f;
constexpr float SHADOW = 10.0f;

NewsSite::NewsSite(const Vector2 &pos, const Vector2 &size, const News &news): ui::ScrollPanel(pos, size), news(news) {
    for (auto &article : news.stonks)
        newsAggregate.push_back(AggregateNews{
            .title = article.summary,
            .subtitle = "Full article available at finance.stonks",
            .image = &NewsImageCache::ref()->stonkImages,
            .imageIdx = article.change > 0 ? 0 : 1
        });
    for (auto &article : news.disasters)
        newsAggregate.push_back(AggregateNews{
            .title = article.summary,
            .subtitle = article.context,
            .image = &(NewsImageCache::ref()->disasterImages),
            .imageIdx = static_cast<int>(article.category)
        });
    
    std::string lotteryNumbers = "";
    for (auto i = 0 ; i < news.lotteryNumbers.size(); i++) {
        lotteryNumbers += std::to_string(news.lotteryNumbers[i]);
        if (i < news.lotteryNumbers.size() - 1)
            lotteryNumbers += "-";
    }

    newsAggregate.push_back(AggregateNews{
        .title = "This month's lottery winners announced!",
        .subtitle = "The winning numbers were: " + lotteryNumbers,
        .image = &NewsImageCache::ref()->lotteryImage
    });
    newsAggregate.push_back(AggregateNews{
        .title = "Today's weather is " + news.weather.summary,
        .subtitle = "Weather News Network",
        .image = &NewsImageCache::ref()->weatherImages,
        .imageIdx = static_cast<int>(news.weather.state)
    });

    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(newsAggregate), std::end(newsAggregate), rng);

    internalSize.y = (GRID_ITEM_HEIGHT + GAP) * newsAggregate.size() + GAP
         + NewsImageCache::ref()->siteTitleImage.height + 2 * GAP;
    addChild(new ui::HR(vec2(0, NewsImageCache::ref()->siteTitleImage.height - 12), vec2(size.x, 0)));
}

void NewsSite::draw(const Vector2 &pos) {
    const float headerHeight = NewsImageCache::ref()->browserHeader.height;

    DrawRectangle(pos.x + SHADOW, pos.y + SHADOW - headerHeight, size.x, size.y + headerHeight, Color{0, 0, 0, 128});
    DrawRectangle(pos.x, pos.y, size.x, size.y, RAYWHITE);
    DrawTexture(NewsImageCache::ref()->browserHeader, pos.x, pos.y - headerHeight, WHITE);
    ui::ScrollPanel::draw(pos);

    const float GRID_ITEM_WIDTH = size.x - 3 * GAP;

    BeginScissorMode(pos.x, pos.y, size.x, size.y);
        DrawTexture(NewsImageCache::ref()->siteTitleImage,
            pos.x + size.x / 2 - NewsImageCache::ref()->siteTitleImage.width / 2,
            pos.y + offsetTop, WHITE);

        for (int i = 0; i < newsAggregate.size(); i++) {
            auto y = GAP + i * (GRID_ITEM_HEIGHT + GAP) + NewsImageCache::ref()->siteTitleImage.height;
            auto x = pos.x + 100;

            // DrawRectangleLines(x, pos.y + y + offsetTop, GRID_ITEM_WIDTH, GRID_ITEM_HEIGHT, BLACK);
            bowser_util::DrawTextBoxed(
                FontCache::ref()->web,
                newsAggregate[i].title.c_str(),
                Rectangle {
                    x + 1 * GAP + IMAGE_WIDTH, pos.y + y + offsetTop,
                    GRID_ITEM_WIDTH - IMAGE_WIDTH - 3 * GAP,
                    GRID_ITEM_HEIGHT - 2 * GAP
                },
                FONT_SIZE * 0.6f, FONT_SPACING, true, BLACK
            );

            bowser_util::DrawTextBoxed(
                FontCache::ref()->web,
                newsAggregate[i].subtitle.c_str(),
                Rectangle {
                    x + 1 * GAP + IMAGE_WIDTH,
                    pos.y + y + offsetTop + GAP / 3 + FONT_SIZE,
                    GRID_ITEM_WIDTH - IMAGE_WIDTH - 3 * GAP,
                    GRID_ITEM_HEIGHT - 2 * GAP - FONT_SIZE
                },
                FONT_SIZE * 0.8f * 0.7f, FONT_SPACING, true, GRAY
            );

            if (newsAggregate[i].image) {
                float h = (float)newsAggregate[i].image->height;
                DrawTexturePro(*(newsAggregate[i].image),
                    Rectangle { newsAggregate[i].imageIdx * h, 0, h, h },
                    Rectangle { x, pos.y + y + offsetTop - FONT_SIZE / 2, IMAGE_WIDTH, IMAGE_HEIGHT },
                    Vector2{0, 0}, 0.0, WHITE);
            }
        }
    EndScissorMode();
}
