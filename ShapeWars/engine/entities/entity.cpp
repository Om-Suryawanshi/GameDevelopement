#include "entity.h"


entity::entity()
{

}

vec2 entity::getPos() const
{
	return pos;
}

void entity::die()
{
	isAlive = false;
}

bool entity::getisAlive() const
{
	return isAlive;
}