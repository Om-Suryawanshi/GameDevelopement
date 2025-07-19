#include "Collision.h"

bool Collision::checkCollision(const entity& a, const entity& b )
{
    float dx = a.getPos().x - b.getPos().x;
    float dy = a.getPos().y - b.getPos().y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (a.getCollisionRadius() + b.getCollisionRadius());
}