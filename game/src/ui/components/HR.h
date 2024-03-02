#ifndef GUI_HR_H
#define GUI_HR_H

#include "raylib.h"
#include "../Style.h"
#include "../../utils/vector_op.h"
#include "./abstract/Component.h"

namespace ui {
    class HR : public Component {
    public:
        HR(
            const Vector2 &pos, 
            const Vector2 &size,
            const Style &style = Style { .borderColor = Color{0, 0, 0, 40} }
        ): Component(pos, size, style) {}

        void draw(const Vector2 &screenPos) override {
            DrawLineEx(screenPos, screenPos + size, style.borderThickness, style.getBorderColor(this));
        }
    };
}

#endif