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

    NewsQuestions(const News& news);
    std::vector<Question> questions;
private:
    News news;

    void addRandomQuestionStock();
    void addRandomQuestionDisaster();
    void addRandomQuestionWeather();
    void addRandomQuestionLottery();
};

#endif