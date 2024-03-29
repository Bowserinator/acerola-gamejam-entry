#include "Scene.h"
#include "../event/EventBuffer.h"
#include "../utils/vector_op.h"
#include "raylib.h"

#include <ranges>
#include <algorithm>

using namespace ui;

Scene::~Scene() {
    for (auto &child : children) {
        delete child;
        child = nullptr;
    }
}

void Scene::removeChild(Component * component) {
    auto itr = std::remove(children.begin(), children.end(), component);
    children.erase(itr, children.end());
    delete *itr;
}

void Scene::update() {
    float dt = GetFrameTime();
    bool mouseConsume = false;

    if (GetMouseDelta() != Vector2{0, 0})
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    for (int i = children.size() - 1; i >= 0; i--) {
        auto child = children[i];

        // -- Input events
        Vector2 localPos = GetMousePosition() - pos;
        Vector2 childLocalPos = localPos - child->pos;
        bool containsCurrentMousePos = child->contains(childLocalPos);

        // -- Mouse movement ---
        if (GetMouseDelta() != Vector2{0, 0}) {
            Vector2 prevLocalPos = GetMousePosition() - GetMouseDelta() - pos;
            bool containsPrevMousePos = child->contains(prevLocalPos - child->pos);
            child->onMouseMoved(childLocalPos);

            if (containsCurrentMousePos && !containsPrevMousePos)
                child->onMouseEnter(childLocalPos);
            else if (!containsCurrentMousePos && containsPrevMousePos)
                child->onMouseLeave(childLocalPos);
        }

        // -- Mouse click --
        int keys[] = { MOUSE_BUTTON_LEFT, MOUSE_BUTTON_MIDDLE, MOUSE_BUTTON_RIGHT, MOUSE_BUTTON_BACK, MOUSE_BUTTON_FORWARD };
        #define MOUSE_CLICK_EVT(evt, childEvt) \
            if (EventBuffer::ref()->evt(key)) { \
                if (containsCurrentMousePos) { \
                    child->childEvt(childLocalPos, key); \
                    mouseConsume = true; \
                } \
            }

        for (auto key: keys) {
            MOUSE_CLICK_EVT(isMouseButtonPressed, onMouseClick);
            MOUSE_CLICK_EVT(isMouseButtonDown, onMouseDown);
            
            if (EventBuffer::ref()->isMouseButtonReleased(key)) {
                child->onMouseRelease(childLocalPos, key);
                mouseConsume = true;
            }
            if (EventBuffer::ref()->isMouseButtonReleased(key) && !containsCurrentMousePos)
                child->unfocus();
        }
        #undef MOUSE_CLICK_EVT

        // -- Mouse scroll --
        if (float scroll = EventBuffer::ref()->getMouseWheelMove()) {
            child->onMouseWheel(childLocalPos, scroll);
            if (containsCurrentMousePos)
                child->onMouseWheelInside(childLocalPos, scroll);
        }

        // -- Keys --
        child->updateKeys(
            EventBuffer::ref()->isKeyDown(KEY_LEFT_SHIFT),
            EventBuffer::ref()->isKeyDown(KEY_LEFT_CONTROL),
            EventBuffer::ref()->isKeyDown(KEY_LEFT_ALT));

        // -- Updates --
        child->tick(dt);
    }
    if (mouseConsume)
        EventBuffer::ref()->consumeMouse();

    ui::Scene::processChildrenDeletions(children);
}

void Scene::draw() {
    for (auto child : children)
        if (!child->getHidden())
            child->draw(child->pos);
}
