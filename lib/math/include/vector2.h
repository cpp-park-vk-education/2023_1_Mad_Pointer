#pragma once

class Vect2 {
public:
    float x;
    float y;

    Vect2() : x(0), y(0) {}
    Vect2(float initX, float initY) : x(initX), y(initY) {}

    bool operator==(const Vect2& rhs) const;
    bool operator!=(const Vect2& rhs) const;

    Vect2 operator+(const Vect2& rhs) const;
    Vect2 operator-(const Vect2& rhs) const;
    Vect2 operator/(const Vect2& rhs) const;
    Vect2 operator*(const Vect2& rhs) const;

    Vect2 operator*(const float value) const;
};
