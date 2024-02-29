#ifndef DIALOG_H
#define DIALOG_H

#include "../utils/types/vector.h"
#include <string>
#include <vector>

using namespace bowser_util;

class DialogBox {
public:
    DialogBox(): pos(vec2(0)), size(vec2(0)), reversed(false) {}
    DialogBox(vec2 pos, vec2 size, bool reversed): pos(pos), size(size), reversed(reversed) {}
    DialogBox(const DialogBox &other): pos(other.pos), size(other.size), reversed(other.reversed) {
        text = other.text;
        choices = other.choices;
    }
    DialogBox &operator=(const DialogBox &other) {
        pos = other.pos;
        size = other.size;
        reversed = other.reversed;
        text = other.text;
        choices = other.choices;
        return *this;
    }

    DialogBox& setText(const std::string &val);
    DialogBox& setChoices(const std::vector<std::string> &choices);

    void tick(float dt);
    void draw();

    // TODO: on select?
    // TODO: dialog manager
    float fontSize = 20.0f;
    float textPercent = 0.0;
private:
    vec2 pos, size;
    std::string text;
    std::vector<std::string> choices;
    bool reversed = false;

    // Get the actual text to display (not 100% revealed)
    std::string getDisplayText() const;
};

#endif