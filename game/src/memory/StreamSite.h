#ifndef STREAM_SITE_H
#define STREAM_SITE_H

// GUI component for streams

#include "../ui/components/abstract/Component.h"
#include "../ui/components/ScrollPanel.h"
#include "News.h"
#include "NewsQuestions.h"

using namespace ui;

class StreamSite : public ui::ScrollPanel {
public:
    StreamSite(const Vector2 &pos, const Vector2 &size, const News &news);

    void draw(const Vector2 &pos) override;
private:
    News news;
    NewsQuestions newsQuestions;
};

#endif