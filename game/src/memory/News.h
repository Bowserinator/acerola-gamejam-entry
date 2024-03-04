#ifndef NEWS_H
#define NEWS_H

#include <array>
#include <vector>
#include <string>

extern const std::vector<std::string> COMPANIES;

struct Stonks {
    std::string company;
    int change;
    std::string summary;

    static Stonks random();
};

struct Disaster {
    enum class Category {
        FIRE, EARTHQUAKE, HURRICANE, VOLCANO,
        PLANE, TRAIN, TERRORISM, INDUSTRIAL,
        last
    };

    Category category;
    std::string context;
    unsigned int dead;
    std::string summary;

    static Disaster random();
};

struct Weather {
    enum class State { SNOWY = 0, SUNNY = 1, RAINY = 2, CLOUDY = 3, STORMY = 4, last = 5 };
    State state;
    std::string summary;

    static Weather random();
};

// News for the current round
class News {
public:
    std::array<int, 3> lotteryNumbers;
    std::vector<Disaster> disasters;
    std::vector<Stonks> stonks;
    Weather weather;

    static News random();
};

#endif