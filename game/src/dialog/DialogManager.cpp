#include "DialogManager.h"
#include "DialogBox.h"
#include "../event/EventBuffer.h"

constexpr double SKIP_COOLDOWN = 0.3;

DialogManager::DialogManager(DialogBox * box): box(box) {
    box->parentManager = this;
}

void DialogManager::update() {
    if (EventBuffer::ref()->isKeyPressed(KEY_X))
        advance();
    
    const auto &node = nodes[currentId];
    if (node.choices.size()) { // Number key select
        int keys[] = { KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE };
        for (int key = 0; key < 9; key++) {
            if (EventBuffer::ref()->isKeyPressed(keys[key]) && node.choices.size() > key) {
                jumpToNode(node.choices[key].second);
                break;
            }
        }   
    }
    
}

void DialogManager::advance() {
    if (currentId == NULL_ID) return;
    const auto &node = nodes[currentId];

    // Show all text, then skip if regular skippable dialog
    if (box->textPercent < 1.0) {
        box->textPercent = 1.0;
    } else if (node.choices.size() == 0 && (GetTime() - lastSkipPress) > SKIP_COOLDOWN) {
        jumpToNode(node.nextId);
        lastSkipPress = GetTime();
    }
}

void DialogManager::jumpToNode(const int nodeId) {
    currentId = nodeId;
    if (nodeId == NULL_ID) {
        box->hide();
        return;
    }
    auto &node = nodes[currentId];
    node.onActive(node);
    box->reversed = !node.forward;
    box->show();
    box->setText(node.text);
    box->setChoices(node.choices);
    box->setTitle(node.title);
    box->titleColor = node.titleColor;
    box->textColor = node.textColor;
}

void DialogManager::setBox(DialogBox * box) {
    box->parentManager = this;
    this->box = box;
}