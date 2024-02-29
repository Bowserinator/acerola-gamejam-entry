#include "DialogBox.h"
#include "../utils/text_wrap.h"
#include "../config.h"
#include "../event/FontCache.h"

#include <cmath>
#include <iostream>

DialogBox& DialogBox::setText(const std::string &val) {
    this->text = val;
    textPercent = 0.0;
    return *this;
}

DialogBox& DialogBox::setChoices(const std::vector<std::string> &choices) {
    this->choices = choices;
    return *this;
}

void DialogBox::tick(float dt) {
    textPercent += 0.8 * dt;
    if (textPercent > 1.0f)
        textPercent = 1.0f;
}

void DialogBox::draw() {
    DrawRectangle(pos.x, pos.y, size.x, size.y, PURPLE);

    bowser_util::DrawTextBoxed(
        FontCache::ref()->main_font,
        getDisplayText().c_str(),
        Rectangle{
            pos.x + DIALOG_BOX_PADDING,
            pos.y + DIALOG_BOX_PADDING,
            size.x - 2 * DIALOG_BOX_PADDING,
            size.y - 2 * DIALOG_BOX_PADDING
        },
        fontSize, FONT_SPACING, true, BLACK);
}

std::string DialogBox::getDisplayText() const {
    std::size_t chars = text.size() - std::round(textPercent * text.size());
    if (!chars) return text;
    if (reversed) // Set the first chars chars to " "
        return std::string(chars, ' ') + text.substr(chars, text.size() - chars);
    // Set the last char chars to " "
    return text.substr(0, text.size() - chars) + std::string(chars, ' ');
}
