#ifndef NEWS_QUESTIONS_H
#define NEWS_QUESITONS_H

#include "News.h"

#include <string>
#include <vector>
#include <array>

class NewsQuestions {
public:
    struct Question {
        std::string question;
        std::vector<std::string> options;
        int correctOption;
    };

    NewsQuestions(News& news);
    std::vector<Question> questions;
private:
    void addRandomQuestionStock(News& news);
    void addRandomQuestionDisaster(const News& news);
    void addRandomQuestionWeather(const News& news);
    void addRandomQuestionLottery(const News& news);
};

#endif