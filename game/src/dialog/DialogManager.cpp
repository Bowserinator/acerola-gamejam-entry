#include "DialogManager.h"
#include "DialogBox.h"
#include "../event/EventBuffer.h"

constexpr double SKIP_COOLDOWN = 0.3;

DialogManager::DialogManager(DialogBox * box): box(box) {
    box->parentManager = this;
}

void DialogManager::update() {
    if (currentId == NULL_ID) return;

    const auto &node = nodes[currentId];

    // X to show all text, then skip if regular skippable dialog
    if (EventBuffer::ref()->isKeyPressed(KEY_X)) {
        if (box->textPercent < 1.0) {
            box->textPercent = 1.0;
        } else if (node.choices.size() == 0 && (GetTime() - lastSkipPress) > SKIP_COOLDOWN) {
            jumpToNode(node.nextId);
            lastSkipPress = GetTime();
        }
    }
}

void DialogManager::jumpToNode(const int nodeId) {
    currentId = nodeId;
    if (nodeId == NULL_ID) {
        box->hide();
        return;
    }
    const auto &node = nodes[currentId];
    box->show();
    box->setText(node.text);
    box->setChoices(node.choices);
}

void DialogManager::setBox(DialogBox * box) {
    box->parentManager = this;
    this->box = box;
}