#pragma once
#include <string>


struct color
{
    float r;
    float g;
    float b;
    color(float red, float green, float blue)
        : r(red), g(green), b(blue) {
    }
};

struct vec2
{
    float x;
    float y;

    vec2() : x(0), y(0) {}
    vec2(float xPos, float yPos) : x(xPos), y(yPos) {}

    vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); }
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); } 
    vec2 operator*(float scalar) const { return vec2(x * scalar, y * scalar); }
    vec2 operator/(float scalar) const { return vec2(x / scalar, y / scalar); }

    vec2& operator+=(const vec2& v) { x += v.x; y += v.y; return *this; }
    vec2& operator-=(const vec2& v) { x -= v.x; y -= v.y; return *this; }

    float dot(const vec2& v) const { return x * v.x + y * v.y; }

    float magnitude() const { return std::sqrt(x * x + y * y); }

    vec2 normalize() const {
        float mag = magnitude();
        if (mag == 0.0f) return vec2(0, 0);
        return vec2(x / mag, y / mag);
    }

    float squaredMagnitude() const {
        return x * x + y * y;
    }
};


struct shape
{
    std::string s_type;
    color s_color;
    std::string s_text;
    vec2 s_position;
    int size;
    vec2 s_velocity;
    shape(const std::string& type, const color& col, const std::string& text,
        const vec2& pos, int sz, const vec2& vel)
        : s_type(type), s_color(col), s_text(text), s_position(pos),
        size(sz), s_velocity(vel) {
    }
};
