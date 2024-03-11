#include "StreamFestSite.h"
#include "../ui/Style.h"
#include "../ui/components/HR.h"
#include "../ui/components/Label.h"
#include "../ui/components/TextButton.h"
#include "../event/FontCache.h"
#include "../utils/text_wrap.h"
#include "../utils/types/vector.h"
#include "../config.h"
#include "../scene/scenes/gameover2.h"
#include "NewsImages.h"

#include <random>
#include <algorithm>
#include <vector>

using namespace bowser_util;

constexpr int MAX_QUESTIONS = 40;

constexpr float SHADOW = 10.0f;
constexpr float GUESS_TIME = 5.0f;

std::vector<SQuestion> QUESTIONS({
    {
        .question = "What will the world population be in 2100?",
        .choices = std::vector<std::string>({
            "4 billion", "11 billion",
            "1 billion", "15 billion"
        }),
        .id = 1
    },
    {
        .question = "Where will most people live in the 22nd century?",
        .choices = std::vector<std::string>({
            "Megacities", "Space colonies",
            "Floating cities", "Same as now"
        }),
        .id = 2
    },
    {
        .question = "What's the furthest celestial body from Earth we will have colonized?",
        .choices = std::vector<std::string>({
            "Earth :(", "The Moon",
            "Mars", "Europa"
        }),
        .id = 3
    },
    {
        .question = "How will the climate change by 2100?",
        .choices = std::vector<std::string>({
            "Reversion to pre-industrial era", "Same as now",
            "Mass desertification", "Surface uninhabitable"
        }),
        .id = 4
    },
    {
        .question = "How will we be primarily be moving around in the future?",
        .choices = std::vector<std::string>({
            "Trains", "Self-driving cars",
            "Flying cars", "Electric scooters"
        }),
        .id = 5
    },
    {
        .question = "Will we have a nuclear war by the 22nd century?",
        .choices = std::vector<std::string>({
            "Small scale exchange", "Nope",
            "Britain nukes itself", "Global thermonuclear war"
        }),
        .id = 6
    },
    {
        .question = "Will we achieve general artificial intelligence?",
        .choices = std::vector<std::string>({
            "No", "Human-level",
            "Above human-level", "Earth consumed for matrioshka brain"
        }),
        .id = 7
    },
    {
        .question = "By what century will we have colonized another star system?",
        .choices = std::vector<std::string>({
            "2400", "2200",
            "2800", "After 3000 CE"
        }),
        .id = 8
    },
    {
        .question = "What will the first fast food restaurant on the moon be?",
        .choices = std::vector<std::string>({
            "MacRonalds", "Burger Queen",
            "Tennessee fried chicken", "A new brand"
        }),
        .id = 9
    },
    {
        .question = "What energy source will dominate the market by 2100?",
        .choices = std::vector<std::string>({
            "Fusion", "Coal",
            "Space-based solar", "Renewables"
        }),
        .id = 10
    },
    {
        .question = "How far will a theory of everything have progressed in 100 years?",
        .choices = std::vector<std::string>({
            "Grand Unified Theory", "Super Grand Unified Theory",
            "Ultra Grand Unified Theory", "Multiversial Unified Theory"
        }),
        .id = 11
    },
    {
        .question = "What will be the dominant government structure in 100 years?",
        .choices = std::vector<std::string>({
            "Autocracy", "Democracy",
            "Monarchy", "AI-run"
        }),
        .id = 12
    },
    {
        .question = "How long will OpenGL remain supported?",
        .choices = std::vector<std::string>({
            "50 years", "20 years",
            "100 years", "200+ years"
        }),
        .id = 13
    }
});


StreamFestSite::StreamFestSite(const Vector2 &pos, const Vector2 &size): ui::ScrollPanel(pos, size) {
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

void StreamFestSite::draw(const Vector2 &pos) {
    if (distortion > 0.0f) {
        distortion -= 0.01f;
        distortion = std::max(0.0f, distortion);
    }
    if (timeLeft > 0.0f && !done) {
        timeLeft -= GetFrameTime();
        if (timeLeft < 0.0f) {
            if (incorrectTotal == 0)
                GAMEOVER_REASON2 = "You didn't answer in time.";
            wrong();
            advanceQuestions();
        }
    }

    const float headerHeight = NewsImageCache::ref()->browserHeader.height;
    DrawRectangle(pos.x + SHADOW, pos.y + SHADOW - headerHeight, size.x, size.y + headerHeight, Color{0, 0, 0, 128});
    DrawRectangle(pos.x, pos.y, size.x, size.y, Color{20, 20, 20, 255});
    DrawTexture(NewsImageCache::ref()->browserHeader, pos.x, pos.y - headerHeight, WHITE);

    DrawRectangle(pos.x, pos.y, size.x * timeLeft / GUESS_TIME, 10.0f, WHITE);

    ui::ScrollPanel::draw(pos);
}

void StreamFestSite::advanceQuestions() {
    if (incorrectTotal >= 1) return;

    question++;
    if (question >= MAX_QUESTIONS) {
        done = true;
        for (auto btn : answerButtons)
            btn->hide()->disable();
        questionLabel->setText("OVER!");
        timeLeft = 0.0f;
        return; // TODO win screen
    }

    timeLeft = GUESS_TIME;

    SQuestion &question = QUESTIONS[rand() % QUESTIONS.size()];
    while (question.id == prevQuestionId) // Don't pick same question twice
        question = QUESTIONS[rand() % QUESTIONS.size()];

    prevQuestionId = question.id;
    questionLabel->setText(question.question);

    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(question.choices), std::end(question.choices), rng);

    for (auto btn : answerButtons)
        btn->hide()->disable();
    int i = 0;
    for (std::string &option : question.choices) {
        answerButtons[i]->show()->enable();
        answerButtons[i]->setText(option);
        answerButtons[i]->setClickCallback([this, &option, &question](){
            auto itr = playerChoices.find(question.id);
            if (itr == playerChoices.end() || itr->second == option)
                correct();
            else {
                if (incorrectTotal == 0)
                    GAMEOVER_REASON2 = "You initially answered '" + itr->second + "'";
                wrong();
            }
            playerChoices[question.id] = option;
            advanceQuestions();
        });
        i++;
    }
}

void StreamFestSite::reset() {
    correctTotal = incorrectTotal = 0;
    distortion = 0.0f;
    playerChoices.clear();
    done = false;
    question = -1;
    prevQuestionId = -1;
    advanceQuestions();
}

void StreamFestSite::correct() {
    std::cout << "CORRECT\n";
    correctTotal++;
}

void StreamFestSite::wrong() {
    std::cout << "WRONG\n";
    distortion = 1.0;
    incorrectTotal++;
}
