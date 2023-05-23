#include "vector2.h"

bool Vec2::operator==(const Vec2& rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const {
    return x != rhs.x || y != rhs.y;
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float value) const {
    return Vec2(x * value, y * value);
}
