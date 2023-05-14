#include "vector2.h"

bool Vect2::operator==(const Vect2& rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Vect2::operator!=(const Vect2& rhs) const {
    return x != rhs.x || y != rhs.y;
}

Vect2 Vect2::operator+(const Vect2& rhs) const {
    return Vect2(x + rhs.x, y + rhs.y);
}

Vect2 Vect2::operator-(const Vect2& rhs) const {
    return Vect2(x - rhs.x, y - rhs.y);
}

Vect2 Vect2::operator*(const float value) const {
    return Vect2(x * value, y * value);
}
