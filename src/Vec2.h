#pragma once
#include <cmath>

struct Vec2 {
    float x;
    float y;

    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const {
        return { x + other.x, y + other.y };
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator-(const Vec2& other) const {
        return { x - other.x, y - other.y };
    }

    Vec2 operator*(const float& other) const {
        return { x * other, y * other };
    }

    Vec2 operator/(const float& other) const {
        return { x / other, y / other };
    }

    float length() const {
        return sqrt(x * x + y * y);
    }

    float lengthSquared() const {
        return x * x + y * y;
    }

    Vec2 normalized() const {
        float len = length();
        if (len < 1e-6f) {
            return { 0, 0 };
        }
        return *this / len;
    }
};