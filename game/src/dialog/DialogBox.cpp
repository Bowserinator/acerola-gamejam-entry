#include "DialogBox.h"
#include "../ui/components/TextButton.h"
#include "../utils/text_wrap.h"
#include "../config.h"
#include "../event/FontCache.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

DialogBox& DialogBox::setText(const std::string &val) {
    this->text = val;
    textPercent = 0.0;
    return *this;
}

DialogBox& DialogBox::setChoices(const ChoiceVector &choices) {
    this->choices = choices;
    addChoices();
    return *this;
}

void DialogBox::tick(float dt) {
    Panel::tick(dt);
    textPercent += 32.0f / std::max((int)text.size(), 1) * dt;
    if (textPercent > 1.0f)
        textPercent = 1.0f;

    if (textPercent == 1.0f) {
        for (auto child : children)
            child->show();
    }
}

void DialogBox::draw(const Vector2 &pos) {
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

    Panel::draw(pos);
}

std::string DialogBox::getDisplayText() const {
    std::size_t chars = text.size() - std::round(textPercent * text.size());
    if (!chars) return text;
    if (reversed) // Set the first chars chars to " "
        return std::string(chars, ' ') + text.substr(chars, text.size() - chars);
    // Set the last char chars to " "
    return text.substr(0, text.size() - chars) + std::string(chars, ' ');
}

void DialogBox::clearChildren() {
    for (auto child : children)
        delete child;
    children.clear();
}

void DialogBox::addChoices() {
    clearChildren();
    int i = 0;
    for (const auto &choice : choices) {
        auto btn = (new ui::TextButton(
            vec2(0, FONT_SIZE + 2 * DIALOG_BOX_PADDING + 40 * i),
            vec2(size.x, 40),
            choice.first
        ))->setClickCallback([this, &choice]() {
            if (!parentManager) throw std::runtime_error("Parent manager was null in DialogBox\n");
            parentManager->jumpToNode(choice.second);
        })->hide();
        addChild(btn);
        i++;
    }
}
