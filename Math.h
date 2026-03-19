#pragma once
#include<random>
struct Vec2 {
    float x;
    float y;

    constexpr Vec2() : x(0), y(0) {}
    constexpr Vec2(float x, float y) : x(x), y(y) {}

    constexpr Vec2 operator+(const Vec2& r) const {
        return { x + r.x, y + r.y };
    }

    constexpr Vec2 operator-(const Vec2& r) const {
        return { x - r.x, y - r.y };
    }

    constexpr Vec2 operator*(float s) const {
        return { x * s, y * s };
    }

    constexpr bool operator==(const Vec2& r)const {
        return x == r.x && y == r.y;
    }
    constexpr Vec2 operator/(float s)const {
        return { x / s,y / s };
    }
};
inline float RandomFloat(float l, float r) {
    float v = (float)(rand()) / RAND_MAX;
    v = v * (r - l) + l;
    return v;
}
