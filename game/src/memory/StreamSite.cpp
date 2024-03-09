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
constexpr float GUESS_TIME = 10.0f;

StreamSite::StreamSite(const Vector2 &pos, const Vector2 &size, const News &news): ui::ScrollPanel(pos, size),
        news(news), newsQuestions(news) {
    constexpr float buttonPad = 10.0f;
    constexpr Vector2 buttonSize{800, 60};

    questionLabel = new ui::Label(vec2(3 * buttonPad, 0), vec2(size.x, 100), "lol tis is the question",
        (Style {
            .horizontalAlign = Style::Align::Left
        }).setAllBackgroundColors(Color{0, 0, 0, 0}));
    addChild(questionLabel);

    auto makeBtn = [this, buttonSize](vec2 pos) {
        return new ui::TextButton(pos, buttonSize, "Choice 1",
        (Style {
            .horizontalAlign = Style::Align::Center
        }).setAllBackgroundColors(Color{0, 0, 0, 0}));
    };

    answerButtons.push_back(makeBtn(vec2(3 * buttonPad, 100)));
    answerButtons.push_back(makeBtn(vec2(3 * buttonPad, 100 + (buttonSize.y + buttonPad) )));
    answerButtons.push_back(makeBtn(vec2(3 * buttonPad, 100 + 2 * (buttonSize.y + buttonPad) )));
    answerButtons.push_back(makeBtn(vec2(3 * buttonPad, 100 + 3 * (buttonSize.y + buttonPad) )));
    for (auto btn : answerButtons)
        addChild(btn);
    advanceQuestions();
}

void StreamSite::draw(const Vector2 &pos) {
    if (distortion > 0.0f) {
        distortion -= 0.01f;
        distortion = std::max(0.0f, distortion);
    }
    if (timeLeft > 0.0f && !done) {
        timeLeft -= GetFrameTime();
        if (timeLeft < 0.0f) {
            wrong();
            advanceQuestions();
        }
    }

    const float headerHeight = NewsImageCache::ref()->browserHeader.height;
    DrawRectangle(pos.x + SHADOW, pos.y + SHADOW - headerHeight, size.x, size.y + headerHeight, Color{0, 0, 0, 128});
    
    DrawRectangle(pos.x, pos.y, size.x, size.y, Color{20, 20, 20, 255});
    if (done) {
        DrawTexture(NewsImageCache::ref()->streamStart, pos.x, pos.y, WHITE);

        int seconds = (int)(GetTime() - endTime);
        std::string time = seconds % 60 < 10 ?
            TextFormat("%d:0%d", seconds / 60, seconds % 60) :
            TextFormat("%d:%d", seconds / 60, seconds % 60);
        auto textSize = MeasureTextEx(FontCache::ref()->main_font, time.c_str(), 1.5f * FONT_SIZE, 0.0f);
        DrawTextEx(FontCache::ref()->main_font, time.c_str(),
            Vector2{ pos.x + size.x / 2 - textSize.x / 2, pos.y + size.y * 0.86f }, 1.5f * FONT_SIZE, 0.0f, WHITE);
    }

    DrawTexture(NewsImageCache::ref()->browserHeader, pos.x, pos.y - headerHeight, WHITE);
    DrawRectangle(pos.x, pos.y, size.x * timeLeft / GUESS_TIME, 10.0f, WHITE);

    if (!done)
        ui::ScrollPanel::draw(pos);
}

void StreamSite::advanceQuestions() {
    question++;
    if (question >= newsQuestions.questions.size()) {
        done = true;
        for (auto btn : answerButtons)
            btn->hide()->disable();
        questionLabel->setText("OVER!");
        timeLeft = 0.0f;
        endTime = GetTime();
        return;
    }

    timeLeft = GUESS_TIME;

    questionLabel->setText(newsQuestions.questions[question].question);

    for (auto btn : answerButtons)
        btn->hide()->disable();
    int i = 0;
    for (auto &option : newsQuestions.questions[question].options) {
        int correctIdx =  newsQuestions.questions[question].correctOption;
        answerButtons[i]->show()->enable();
        answerButtons[i]->setText(option);
        if (i == correctIdx)
            answerButtons[i]->setClickCallback([this](){correct(); advanceQuestions(); });
        else
            answerButtons[i]->setClickCallback([this](){wrong(); advanceQuestions();});
        i++;
    }
}

void StreamSite::reset() {
    correctTotal = incorrectTotal = 0;
    distortion = 0.0f;
    done = false;
    question = -1;
    timeLeft = 0.0f;
    advanceQuestions();
}

void StreamSite::correct() {
    std::cout << "CORRECT\n";
    correctTotal++;
}

void StreamSite::wrong() {
    std::cout << "WRONG\n";
    distortion = 1.0;
    // incorrectTotal++;
}
