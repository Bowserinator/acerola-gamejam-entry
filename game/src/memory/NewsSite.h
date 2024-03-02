#ifndef NEWS_SITE_H
#define NEWS_SITE_H

// GUI component for news site

#include "../ui/components/abstract/Component.h"
#include "../ui/components/ScrollPanel.h"
#include "News.h"

#include <vector>
#include <string>

using namespace ui;

class NewsSite : public ui::ScrollPanel {
public:
    NewsSite(const Vector2 &pos, const Vector2 &size, const News &news);

    void draw(const Vector2 &pos) override;
private:
    News news;

    struct AggregateNews {
        std::string title;
        std::string subtitle = "";
        Texture * image = nullptr;
        int imageIdx = 0;
    };

    std::vector<AggregateNews> newsAggregate;
};

#endif