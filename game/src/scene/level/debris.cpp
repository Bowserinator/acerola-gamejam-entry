#include "debris.h"
#include "raylib.h"
#include "../../utils/math.h"

void Debris::tick(float dt) {
    moveAnimation.tick();

    auto progress = moveAnimation.progress();
    pos = startPos.lerp(targetPos, progress);
    rotation = bowser_util::lerp(startRotation, targetRotation, progress);
}

void Debris::draw() {
    DrawRectanglePro(Rectangle { pos.x, pos.y, 32, 32 }, vec2(0), rotation, RED);
}
