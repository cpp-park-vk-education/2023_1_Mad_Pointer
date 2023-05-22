#pragma once

class Vec2 {
public:
    float x;
    float y;

    Vec2() : x(0), y(0) {}
    Vec2(float initX, float initY) : x(initX), y(initY) {}

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator/(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& rhs) const;

    Vec2 operator*(const float value) const;
};
