#include "Panel.h"
#include "../Scene.h"
#include "../../event/EventBuffer.h"
#include "../../utils/vector_op.h"

#include <ranges>
#include <algorithm>

ui::Panel::Panel(const Vector2 &pos, const Vector2 &size, const Style &style): ui::InteractiveComponent(pos, size, style) {}

ui::Panel::~Panel() {
    for (auto &child : children) {
        delete child;
        child = nullptr;
    }
}

void ui::Panel::tick(float dt) {
    for (auto child : children)
        child->tick(dt);
}

void ui::Panel::draw(const Vector2 &screenPos) {
    InteractiveComponent::draw(screenPos);
    for (auto child : children)
        if (!child->getHidden())
            child->draw(Vector2{ screenPos.x + child->pos.x, screenPos.y + child->pos.y });
}

void ui::Panel::addChild(Component * component) {
    component->setParent(this);
    component->setParentScene(parentScene);
    children.push_back(component);
}

void ui::Panel::setParentScene(Scene * scene) {
    parentScene = scene;
    for (auto child : children)
        child->setParentScene(scene);
}

void ui::Panel::removeChild(Component * component) {
    auto itr = std::remove(children.begin(), children.end(), component);
    children.erase(itr, children.end());
    delete *itr;
}

ui::Component * ui::Panel::getChildIdx(std::size_t idx) {
    return children[idx];
}

std::size_t ui::Panel::getChildCount() const {
    return children.size();
}

void ui::Panel::onUnfocus() {
    for (auto child : children)
        child->unfocus();
}

// Propogate rest of the events
#define PROPOGATE_EVENT(evt) for (int i = children.size() - 1; i >= 0; i--) { \
        auto child = children[i]; \
        if (child->contains(localPos + eventDelta - child->pos)) { \
            child->evt(localPos + eventDelta - child->pos); \
            break; \
        }}
#define PROPOGATE_EVENT_VAR(evt, var) for (int i = children.size() - 1; i >= 0; i--) { \
        auto child = children[i];\
        if (child->contains(localPos + eventDelta - child->pos)) { \
            child->evt(localPos + eventDelta - child->pos, var); \
            break; \
        }}

void ui::Panel::onMouseMoved(Vector2 localPos) {
    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];
        child->onMouseMoved(localPos + eventDelta - child->pos);
    }

    Vector2 prevLocalPos = localPos - GetMouseDelta();
    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];
        bool containsNow = child->contains(localPos + eventDelta - child->pos);
        bool containsPrev = child->contains(prevLocalPos + eventDelta - child->pos); 

        if (containsPrev && !containsNow)
            child->onMouseLeave(localPos + eventDelta - child->pos);
        if (!containsPrev && containsNow)
            child->onMouseEnter(localPos + eventDelta - child->pos);
    }
}
void ui::Panel::onMouseEnter(Vector2 localPos) {
    PROPOGATE_EVENT(onMouseEnter)
}
void ui::Panel::onMouseLeave(Vector2 localPos) {
    Vector2 prevLocalPos = localPos - GetMouseDelta();
    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];
        if (child->contains(prevLocalPos + eventDelta - child->pos))
            child->onMouseLeave(localPos + eventDelta - child->pos);
    }
}
void ui::Panel::onMouseDown(Vector2 localPos, unsigned button) {
    PROPOGATE_EVENT_VAR(onMouseDown, button)
}
void ui::Panel::onMouseRelease(Vector2 localPos, unsigned button) {
    for (auto child : children)
        child->onMouseRelease(localPos + eventDelta - child->pos, button);
}
void ui::Panel::onMouseClick(Vector2 localPos, unsigned button) {
    bool alreadyClicked = false;
    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];
        if (child->contains(localPos + eventDelta - child->pos) && !alreadyClicked) {
            child->onMouseClick(localPos + eventDelta - child->pos, button);
            alreadyClicked = true;
        } else {
            child->unfocus();
        }
    }
}
void ui::Panel::onMouseWheelInside(Vector2 localPos, float d) {
    PROPOGATE_EVENT_VAR(onMouseWheelInside, d)
}

void ui::Panel::onMouseWheel(Vector2 localPos, float d) {
    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];
        child->onMouseWheel(localPos + eventDelta - child->pos, d);
    }
}

void ui::Panel::updateKeys(bool shift, bool ctrl, bool alt) {
    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];
        child->updateKeys(shift, ctrl, alt);
    }
}

void ui::Panel::processDeletion() {
    ui::Scene::processChildrenDeletions(children);
}
