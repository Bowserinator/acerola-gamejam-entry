#ifndef DIALOG_H
#define DIALOG_H

#include "../utils/types/vector.h"
#include "../config.h"
#include "../ui/components/Panel.h"

#include <string>
#include <vector>

using namespace bowser_util;

class DialogBox : public ui::Panel {
public:
    DialogBox(): Panel(vec2(0), vec2(0)), reversed(false) {}
    DialogBox(vec2 pos, vec2 size, bool reversed): Panel(pos, size), reversed(reversed) {}
    DialogBox(const DialogBox &other): Panel(other.pos, other.size), reversed(other.reversed) {
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

    void tick(float dt) override;
    void draw(const Vector2 &pos) override;

    // TODO: on select?
    // TODO: dialog manager
    float fontSize = FONT_SIZE;
    float textPercent = 0.0;
private:
    std::string text;
    std::vector<std::string> choices;
    bool reversed = false;

    // Get the actual text to display (not 100% revealed)
    std::string getDisplayText() const;
};

#endif