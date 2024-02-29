#include <algorithm>
#include <iostream>
#include <limits>

#include "CollisionBox.h"

constexpr float MAX_F = std::numeric_limits<float>::max();

// Perform vertical line collision, returning distance squared from start to collision point
// or MAX_F if there is no such collision point
// @param vert1 Vert 1 of the vertical line, vert1.x = vert2.x
// @param vert2 Vert 2 of the vertical line
// @param line1 Start vertex (should be previous position, distance is relative to this)
// @param line2 End of intersection line
// @return dis^2 from line1
float verticalLineCollide(const vec2 vert1, const vec2 vert2, const vec2 line1, const vec2 line2) {
    if (line1.x == line2.x) // Vertical line cannot collide with vertical line
        return MAX_F;

    const vec2 collidePoint = line1 + (line2 - line1).normalize() * std::abs(vert1.x - line1.x);
    if (collidePoint.y <= vert2.y && collidePoint.y >= vert1.y)
        return collidePoint.distanceSqr(line1);
    return MAX_F;
}

// Perform horizontal line collision, returning distance squared from start to collision point
// or MAX_F if there is no such collision point
// @param vert1 Vert 1 of the horizontal line, vert1.y = vert2.y
// @param vert2 Vert 2 of the horizontal line
// @param line1 Start vertex (should be previous position, distance is relative to this)
// @param line2 End of intersection line
// @return dis^2 from line1
float horizontalLineCollide(const vec2 vert1, const vec2 vert2, const vec2 line1, const vec2 line2) {
    if (line1.y == line2.y) // Horz cannot collide with horz
        return MAX_F;

    const vec2 collidePoint = line1 + (line2 - line1).normalize() * std::abs(vert1.y - line1.y);
    if (collidePoint.x <= vert2.x && collidePoint.x >= vert1.x)
        return collidePoint.distanceSqr(line1);
    return MAX_F;
}


void CollisionBox::pushSelfOutsideOf(const CollisionBox &other, const vec2 &velHint) {
    if (!isColliding(other)) return; // Ok we're technically skipping over thin colliders here

    vec2 currPos = vec2(x, y);
    vec2 prevPos = vec2(x - velHint.x, y - velHint.y);

    float top = MAX_F;
    float bottom = MAX_F;
    float left = MAX_F;
    float right = MAX_F;

    if (velHint.y > 0)
        top = std::min(
            horizontalLineCollide(vec2(other.x, other.y), vec2(other.x + other.width, other.y),
                prevPos + vec2(0, height), currPos + vec2(0, height)),
            horizontalLineCollide(vec2(other.x, other.y), vec2(other.x + other.width, other.y),
                prevPos + vec2(width, height), currPos + vec2(width, height))
        );
    else if (velHint.y < 0)
        bottom = std::min(
            horizontalLineCollide(vec2(other.x, other.y + other.height), vec2(other.x + other.width, other.y + other.height), 
                prevPos, currPos),
            horizontalLineCollide(vec2(other.x, other.y + other.height), vec2(other.x + other.width, other.y + other.height), 
                prevPos + vec2(width, 0), currPos + vec2(width, 0))
        );
    if (velHint.x > 0)
        left = std::min(
            verticalLineCollide(vec2(other.x, other.y), vec2(other.x, other.y + other.height),
                prevPos + vec2(width, 0), currPos + vec2(width, 0)),
            verticalLineCollide(vec2(other.x, other.y), vec2(other.x, other.y + other.height),
                prevPos + vec2(width, height), currPos + vec2(width, height))
        );
    else if (velHint.x < 0)
        right = std::min(
            verticalLineCollide(vec2(other.x + other.width, other.y), vec2(other.x + other.width, other.y + other.height),
                prevPos, currPos),
            verticalLineCollide(vec2(other.x + other.width, other.y), vec2(other.x + other.width, other.y + other.height),
                prevPos + vec2(0, height), currPos + vec2(0, height))
        );

    // Y collision is closer
    if (std::min(top, bottom) <= std::min(left, right)) {
        if (top < bottom && top < MAX_F) {
            y = std::min(y, other.y - height);
            onPush(other, FACE::TOP);
        }
        else if (bottom < top && bottom < MAX_F) {
            y = std::max(y, other.y + other.height);
            onPush(other, FACE::BOTTOM);
        }
    } 
    // X collision is closer
    else {
        if (left < right && left < MAX_F) {
            x = std::min(x, other.x - width);
            onPush(other, FACE::LEFT);
        }
        else if (right < left && right < MAX_F) {
            x = std::max(x, other.x + other.width);
            onPush(other, FACE::RIGHT);
        }
    }
}

bool CollisionBox::isColliding(const CollisionBox &other) {
    bool result = CheckCollisionRecs(*this, other);
    if (result) onCollide(other);
    return result;
}
