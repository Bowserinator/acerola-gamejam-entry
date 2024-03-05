#include "NewsQuestions.h"
#include "News.h"
#include "raylib.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>

template <class T>
int shuffle(std::vector<T> &vec, int correct) {
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    T org = vec[correct];
    std::shuffle(std::begin(vec), std::end(vec), rng);

    for (int i = 0; i < vec.size(); i++)
        if (vec[i] == org)
            return i;
    throw std::runtime_error("Could not find original match");
}

template <class T>
void shuffle2(std::vector<T> &vec) {
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(vec), std::end(vec), rng);
}

NewsQuestions::NewsQuestions(const News& news): news(news) {
    addRandomQuestionLottery();

    std::vector<int> tmp = hard_mode ?
        std::vector<int>({1, 2, 1, 2, 3}) :
        std::vector<int>({1, 2, 3});
    shuffle2(tmp);
    for (auto i : tmp) {
        if (i == 1) addRandomQuestionStock();
        if (i == 2) addRandomQuestionDisaster();
        if (i == 3) addRandomQuestionWeather();
    }

    // for (auto &question : questions) {
    //     std::cout << question.question << "\n";
    //     for (auto &option : question.options)
    //         std::cout << "- " << option << "\n";
    //     std::cout << "correct: " << question.correctOption << "\n----\n";
    // }
}

void NewsQuestions::addRandomQuestionStock() {
    std::string goingUpCompany = "";
    int change = 0;

    for (const auto &company : news.stonks)
        if (company.change > 0) {
            goingUpCompany = company.company;
            change = company.change;
            if (rand() % 2 == 0)
                break;
        }

    if (goingUpCompany.size() && rand() % 2 != 0) {
        std::vector<std::string> goingDownCompanies; // Companies that arent going up
        std::copy_if(COMPANIES.begin(), COMPANIES.end(), std::back_inserter(goingDownCompanies), [this](auto x) {
            for (const auto &company : news.stonks)
                if (company.company == x && company.change > 0)
                    return false;
            return true;
        });

        auto opt1 = std::vector<std::string>({
            goingDownCompanies[0],
            goingDownCompanies[1],
            goingDownCompanies[2],
            goingUpCompany
        });
        auto correct1 = shuffle(opt1, 3);

        questions.push_back(Question {
            .question = "Now, which company was it that will rise in stock?",
            .options = opt1,
            .correctOption = correct1
        });

        std::vector<int> opt2;
        opt2.push_back(change);
        for (int i = 0; i < 3; i++) {
            int randChange;
            do {
                randChange = GetRandomValue(1, 50);
            } while (std::find(opt2.begin(), opt2.end(), randChange) != opt2.end());
            opt2.push_back(randChange);
        }
        int correct2 = shuffle(opt2, 0);

        questions.push_back(Question {
            .question = "Give a percent change in stock value:",
            .options = std::vector<std::string>({
                std::to_string(opt2[0]) + "%",
                std::to_string(opt2[1]) + "%",
                std::to_string(opt2[2]) + "%",
                std::to_string(opt2[3]) + "%"
            }),
            .correctOption = correct2
        });
    } else {
        shuffle2(news.stonks);
        for (int i = 0; i < std::min(2, (int)news.stonks.size()); i++) {
            auto &stonk = news.stonks[i];

            std::vector<int> opt2;
            for (int i = 0; i < 4; i++) {
                int randChange;
                do {
                    randChange = GetRandomValue(i < 2 ? -50 : -1, i < 2 ? 1 : 50);
                } while (std::find(opt2.begin(), opt2.end(), randChange) != opt2.end());
                opt2.push_back(randChange);
            }
            int correct = stonk.change < 0 ? 0 : 2;
            opt2[correct] = stonk.change;
            correct = shuffle(opt2, correct);

            questions.push_back(Question {
                .question = "How will " + stonk.company + " stock do?",
                .options = std::vector<std::string>({
                    (opt2[0] < 0 ? "Down " : "Up ") + std::to_string(std::abs(opt2[0])) + "%",
                    (opt2[1] < 0 ? "Down " : "Up ") + std::to_string(std::abs(opt2[1])) + "%",
                    (opt2[2] < 0 ? "Down " : "Up ") + std::to_string(std::abs(opt2[2])) + "%",
                    (opt2[3] < 0 ? "Down " : "Up ") + std::to_string(std::abs(opt2[3])) + "%",
                }),
                .correctOption = correct
            });
        }
    }
}

void NewsQuestions::addRandomQuestionDisaster() {
    // Which disaster will occur?
    Disaster::Category disaster1 = static_cast<Disaster::Category>(rand() % static_cast<int>(Disaster::Category::last));
    Disaster::Category disaster2 = static_cast<Disaster::Category>(rand() % static_cast<int>(Disaster::Category::last));
    while (disaster1 == disaster2)
        disaster2 = static_cast<Disaster::Category>(rand() % static_cast<int>(Disaster::Category::last));

    bool d1Occurs = std::find_if(news.disasters.begin(), news.disasters.end(),
        [disaster1](auto x) { return x.category == disaster1; }) != news.disasters.end();
    bool d2Occurs = std::find_if(news.disasters.begin(), news.disasters.end(),
        [disaster2](auto x) { return x.category == disaster2; }) != news.disasters.end();

    int correct = 0;
    if (d1Occurs && d2Occurs) correct = 2;
    else if (d1Occurs) correct = 0;
    else if (d2Occurs) correct = 1;
    else correct = 3;

    auto disasterToString = [](Disaster::Category category) {
        switch(category) {
            case Disaster::Category::FIRE: return "Fire";
            case Disaster::Category::EARTHQUAKE: return "Earthquake";
            case Disaster::Category::HURRICANE: return "Hurricane";
            case Disaster::Category::VOLCANO: return "Volcanic disaster";
            case Disaster::Category::PLANE: return "Plane accident";
            case Disaster::Category::TRAIN: return "Train accident";
            case Disaster::Category::TERRORISM: return "Terrorism / Crime";
            case Disaster::Category::INDUSTRIAL: return "Industrial accident";
        }
        return "???";
    };

    questions.push_back(Question {
        .question = "Finally, which of the following will occur?",
        .options = std::vector<std::string>({
            disasterToString(disaster1),
            disasterToString(disaster2),
            "Both", "None"
        }),
        .correctOption = correct
    });

    // -------------------
    // Context question:
    auto addRandomHeadline = [&](const std::string &question) {
        std::vector<std::string> opts({ news.disasters[rand() % news.disasters.size()].summary });
        correct = 0;

        while (opts.size() < 4) {
            std::string headline = Disaster::random().summary;
            if (std::find(opts.begin(), opts.end(), headline) == opts.end())
                opts.push_back(headline);
        }
        correct = shuffle(opts, correct);
        questions.push_back(Question {
            .question = question,
            .options = opts,
            .correctOption = correct
        });
    };

    bool altQuestion = news.disasters.size() == 1;
    addRandomHeadline(altQuestion ?
        "Can you give us a headline that you remember?" :
        "Can you give us another headline you remember?");

    // -------------------
    // How many people died in total?
    if (altQuestion) {
        int totalDeaths = std::transform_reduce(news.disasters.begin(), news.disasters.end(), 0, std::plus{},
            [](auto val) { return val.dead; });
        std::vector<std::string> opts2({ std::to_string(totalDeaths) });
        while (opts2.size() < 4) {
            std::string counts = std::to_string(GetRandomValue(1, 500));
            if (std::find(opts2.begin(), opts2.end(), counts) == opts2.end())
                opts2.push_back(counts);
        }

        correct = 0;
        correct = shuffle(opts2, correct);

        questions.push_back(Question {
            .question = "How many people TOTAL will die in a disaster by next month?",
            .options = opts2,
            .correctOption = correct
        });
    } else {
        addRandomHeadline("Can you give us a headline that you remember?");
    }
}

void NewsQuestions::addRandomQuestionWeather() {
    int * conditions = LoadRandomSequence(4, 0, static_cast<int>(Weather::State::last) - 1);
    int correct = static_cast<int>(news.weather.state);
    int correctIdx = -1;
    bool alreadyContains = false;

    for (int i = 0; i < 4; i++) {
        if (conditions[i] == correct) {
            correctIdx = i;
            alreadyContains = true;
            break;
        }
    }
    if (!alreadyContains) {
        correctIdx = GetRandomValue(0, 3);
        conditions[correctIdx] = correct;
    }

    Question returned { .question = "What'll the weather be 1 month from now?", .correctOption = correctIdx };
    for (int i = 0; i < 4; i++) {
        std::string name = "";
        switch (static_cast<Weather::State>(conditions[i])) {
            case Weather::State::SNOWY: name = "Snowy"; break;
            case Weather::State::SUNNY: name = "Sunny"; break;
            case Weather::State::RAINY: name = "Rainy"; break;
            case Weather::State::CLOUDY: name = "Cloudy"; break;
            case Weather::State::STORMY: name = "Stormy"; break;
        }
        returned.options.push_back(name);
    }
    questions.push_back(returned);
    UnloadRandomSequence(conditions);
}

void NewsQuestions::addRandomQuestionLottery() {
    // Randomizations:
    // Either all
    // 1. all permutations
    // 2. all random
    if (rand() % 2 == 0) { // All permutations
        auto p1 = news.lotteryNumbers;
        std::next_permutation(p1.begin(), p1.end());
        auto p2 = p1;
        std::next_permutation(p2.begin(), p2.end());
        auto p3 = p2;
        std::next_permutation(p3.begin(), p3.end());

        std::vector<std::string> opts({
            std::string(TextFormat("%d-%d-%d", news.lotteryNumbers[0], news.lotteryNumbers[1], news.lotteryNumbers[2])),
            std::string(TextFormat("%d-%d-%d", p1[0], p1[1], p1[2])),
            std::string(TextFormat("%d-%d-%d", p2[0], p2[1], p2[2])),
            std::string(TextFormat("%d-%d-%d", p3[0], p3[1], p3[2])),
        });
        int correct = 0;
        shuffle(opts, correct);

        questions.push_back(Question {
            .question = "Finally, what are the winning lottery numbers?",
            .options = opts,
            .correctOption = correct
        });
    } else {
        std::vector<std::string> opts({
            std::string(TextFormat("%d-%d-%d", news.lotteryNumbers[0], news.lotteryNumbers[1], news.lotteryNumbers[2])),
            std::string(TextFormat("%d-%d-%d", GetRandomValue(0, 99), GetRandomValue(0, 99), GetRandomValue(0, 99))),
            std::string(TextFormat("%d-%d-%d", GetRandomValue(0, 99), GetRandomValue(0, 99), GetRandomValue(0, 99))),
            std::string(TextFormat("%d-%d-%d", GetRandomValue(0, 99), GetRandomValue(0, 99), GetRandomValue(0, 99))),
        });
        int correct = 0;
        shuffle(opts, correct);

        questions.push_back(Question {
            .question = "Finally, what are the winning lottery numbers?",
            .options = opts,
            .correctOption = correct
        });
    }
}
