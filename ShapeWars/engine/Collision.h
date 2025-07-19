#pragma once
#pragma once
#include "../engine/entities/entity.h"
#include <cmath>


class Collision
{
public:
    bool checkCollision(const entity& a, const entity& b);
};