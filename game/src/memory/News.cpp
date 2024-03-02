#include "News.h"
#include "raylib.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

const std::vector<std::string> COMPANIES({
    "Macrohard Co.",
    "Pear Inc",
    "MIYIDIA",
    "Jungle",
    "Alpha Inc",
    "Facedoor",
    "Edison",
    "21st century group",
    "BMD",
    "Acerola Co.",
    "Webflix Inc",
    "Stardollars",
    "Burger Queen",
    "S-mobile",
    "T-Witch",
    "Ourtube",
    "Mozzarella"
});

const std::vector<std::string> STOCK_MESSAGES_GOOD({
    "{company} stock has gone up by {percent}% this quarter",
    "{company} reports record profits, shares go up by {percent}%",
    "Why {company} stock jumped by {percent}% this month",
    "{company} stock rockets up by {percent}%",
    "Record prices as {company} stock rises by {percent}%"
});
const std::vector<std::string> STOCK_MESSAGES_BAD({
    "{company} stock has gone down by {percent}% this quarter",
    "{company} value plummets, shares fall by {percent}%",
    "Shares fall by {percent}%, {company} may declare bankruptcy",
    "{company} CEO retires, stock plunges by {percent}%",
    "{company} CEO arrested, stock plummets by {percent}%"
});

std::string randStr(const std::vector<std::string> &choices) {
    return choices[GetRandomValue(0, choices.size() - 1)];
}

std::string replace(std::string s, const std::string &old_s, const std::string &new_s) {
    while(s.find(old_s) != std::string::npos) s.replace(s.find(old_s), old_s.size(), new_s);
    return s;
}

Stonks Stonks::random() {
    auto company = COMPANIES[GetRandomValue(0, COMPANIES.size() - 1)];
    auto change = GetRandomValue(-50, 50);
    auto summary = change < 0 ?
        STOCK_MESSAGES_GOOD[GetRandomValue(0, STOCK_MESSAGES_GOOD.size() - 1)] :
        STOCK_MESSAGES_BAD[GetRandomValue(0, STOCK_MESSAGES_BAD.size() - 1)];
    if (change == 0)
        summary = company + " stock remains unchanged";
    else {
        summary = replace(summary, "{company}", company);
        summary = replace(summary, "{percent}", std::to_string(std::abs(change)));
    }

    auto r = Stonks {
        .company = company,
        .change = change,
        .summary = summary
    };
    return r;
}


const std::vector<std::string> FIRE_TITLES({
    "Fire rips through orphanage",
    "Wildfires continue to blaze through countryside",
    "Chemical plant fire caused by lit cigarette",
    "Old factory fire was arson, police say",
    "Fire burns down mascot horror attraction",
    "Fire engine burns down in ironic accident",
    "Oil rig catches on fire!",
    "Residents warned of wildfire smoke",
    "Poor code causes datacenter fire"
});
const std::vector<std::string> EARTHQUAKE_TITLES({
    "Earthquake ravages city",
    "Yet another 'once in a century' earthquake",
    "Recent earthquake may be caused by nuclear testing",
    "Repeated quakes devastate city",
    "Earthquake opens huge sinkhole",
    "Many left without electricity after earthquake",
    "Earthquake-triggered tsunami floods coastal city",
    "Several landslides caused by earthquakes"
});
const std::vector<std::string> HURRICANE_TITLES({
    "Hurricane leaves thousands without power",
    "Hurricane devastates costal city",
    "Typhoon devastates costal city",
    "City ravaged by passing cyclone"
});
const std::vector<std::string> VOLCANO_TITLES({
    "Miniature-volcano forms in the middle of a school",
    "Volcanic eruption displaces thousands",
    "Undersea volcano causes tsunami",
    "Volcanic eruption throws planes in a frenzy"
});
const std::vector<std::string> PLANE_TITLES({
    "Plane crash caused by faulty equipment",
    "Plane wheel falls off on runway",
    "Disaster: airline pilot used ChatGPT to navigate",
    "Passenger plane flies into goose",
    "Pilot finds fuel tank was filled with lemonade",
    "Plane accidentally shot down by missile crew"
});
const std::vector<std::string> TRAIN_TITLES({
    "Train derails on mountainside",
    "Freight train crashes into warehouse",
    "Disaster! Cow wanders onto rail tracks"
});
const std::vector<std::string> TERRORISM_TITLES({
    "Bank robbery live: robbers were armed",
    "Cyber-criminals hack hospital",
    "Armed insurgents rush mall",
    "Car bomb goes off in city",
    "Poison gas dropped in subway",
    "Coca-cola murderer caught"
});
const std::vector<std::string> INDUSTRIAL_TITLES({
    "Chemical plant explodes due to faulty wiring",
    "Nuclear plant operator 'forgot' to turn off reactor",
    "Gas pipeline ruptures, residents collect free gas",
    "Toxic fumes leak from storage facility",
    "Mine collapse traps workers",
    "Dam failure floods local farmland",
    "Construction vehicle hijacked by 3 year old",
    "Oil tanker sinks at sea"
});

Disaster Disaster::random() {
    Disaster::Category category = static_cast<Disaster::Category>(GetRandomValue(0, (int)Disaster::Category::last - 1));
    unsigned int dead = GetRandomValue(1, 500);
    std::string summary = "";
    switch(category) {
        case Disaster::Category::FIRE:
            summary = randStr(FIRE_TITLES); break;
        case Disaster::Category::EARTHQUAKE:
            summary = randStr(EARTHQUAKE_TITLES); break;
        case Disaster::Category::HURRICANE:
            summary = randStr(HURRICANE_TITLES); break;
        case Disaster::Category::VOLCANO:
            summary = randStr(VOLCANO_TITLES); break;
        case Disaster::Category::PLANE:
            summary = randStr(PLANE_TITLES); break;
        case Disaster::Category::TRAIN:
            summary = randStr(TRAIN_TITLES); break;
        case Disaster::Category::TERRORISM:
            summary = randStr(TERRORISM_TITLES); break;
        case Disaster::Category::INDUSTRIAL:
            summary = randStr(INDUSTRIAL_TITLES); break;
    }

    return Disaster {
        .category = category,
        .context = "",
        .dead = dead,
        .summary = summary
    };
}

Weather Weather::random() {
    auto state = static_cast<Weather::State>(GetRandomValue(0, (int)Weather::State::last - 1));
    std::string name = "";
    switch(state) {
        case State::SNOWY: { name = "Snowy"; break; }
        case State::SUNNY: { name = "Sunny"; break; }
        case State::RAINY: { name = "Rainy"; break; }
        case State::CLOUDY: { name = "Cloud"; break; }
        case State::STORMY: { name = "Stormy"; break; }
        default: { name = "???"; break; }
    }
    return Weather {
        .state = state,
        .summary = name 
    };
}

News News::random() {
    auto r = News {
        .weather = Weather::random()
    };
    int stonksCount = GetRandomValue(1, 4);
    int disasterCount = GetRandomValue(0, 2);

    while (r.stonks.size() < stonksCount) {
        auto stonk = Stonks::random();
        if (r.stonks.end() == std::find_if(r.stonks.begin(), r.stonks.end(), [&](auto x) { return x.company == stonk.company; }))
            r.stonks.push_back(stonk);
    }
    for (auto i = 0; i < disasterCount; i++)
        r.disasters.push_back(Disaster::random());

    for (auto i = 0; i < r.lotteryNumbers.size(); i++)
        r.lotteryNumbers[i] = GetRandomValue(0, 99);

    for (auto &i : r.disasters)
        std::cout << i.summary << "\n";
    std::cout << "---\n";
    for (auto &i : r.stonks)
        std::cout << i.summary << "\n";
    std::cout << "---\n";

    return r;
}
