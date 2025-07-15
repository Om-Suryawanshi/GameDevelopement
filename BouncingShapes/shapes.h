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

struct position
{
    float x;
    float y;
    position(float xPos, float yPos)
        : x(xPos), y(yPos) {
    }
};

struct velocity
{
    float x;
    float y;
    velocity(float xVel, float yVel)
        : x(xVel), y(yVel) {
    }
};

struct shape
{
    std::string s_type;
    color s_color;
    std::string s_text;
    position s_position;
    int size;
    velocity s_velocity;
    shape(const std::string& type, const color& col, const std::string& text,
        const position& pos, int sz, const velocity& vel)
        : s_type(type), s_color(col), s_text(text), s_position(pos),
        size(sz), s_velocity(vel) {
    }
};
