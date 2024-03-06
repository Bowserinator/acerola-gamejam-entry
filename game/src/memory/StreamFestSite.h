#ifndef STREAM_SITE2_H
#define STREAM_SITE2_H

#include "../ui/components/abstract/Component.h"
#include "../ui/components/ScrollPanel.h"
#include "../ui/components/TextButton.h"
#include "../ui/components/Label.h"
#include <unordered_map>

using namespace ui;

struct SQuestion {
    std::string question;
    std::vector<std::string> choices;
    int id;
};

class StreamFestSite : public ui::ScrollPanel {
public:
    StreamFestSite(const Vector2 &pos, const Vector2 &size);

    void draw(const Vector2 &pos) override;

    void reset();

    float distortion = 0.0f;
    float timeLeft = 0.0f;
    bool done = false;

    int correctTotal;
    int incorrectTotal;
    int question = -1;
    int prevQuestionId = -1;
private:
    ui::Label * questionLabel;
    std::vector<ui::TextButton *> answerButtons;

    std::unordered_map<int, std::string> playerChoices; // question id -> choice

    void advanceQuestions();
    void correct();
    void wrong();
};

#endif