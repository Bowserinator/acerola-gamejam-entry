#ifndef STREAM_SITE_H
#define STREAM_SITE_H

// GUI component for streams

#include "../ui/components/abstract/Component.h"
#include "../ui/components/ScrollPanel.h"
#include "../ui/components/TextButton.h"
#include "../ui/components/Label.h"
#include "News.h"
#include "NewsQuestions.h"

using namespace ui;

class StreamSite : public ui::ScrollPanel {
public:
    StreamSite(const Vector2 &pos, const Vector2 &size, const News &news);

    void draw(const Vector2 &pos) override;

    void reset();

    float distortion = 0.0f;
    float timeLeft = 0.0f;
    bool done = false;
    double endTime = 0.0;

    int correctTotal;
    int incorrectTotal;
private:
    News news;
    NewsQuestions newsQuestions;
    ui::Label * questionLabel;
    std::vector<ui::TextButton *> answerButtons;
    int question = -1;

    void advanceQuestions();
    void correct();
    void wrong();
};

#endif