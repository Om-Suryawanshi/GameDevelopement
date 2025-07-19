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

void entity::pause() 
{
	paused = !paused;
}

float entity::getCollisionRadius() const
{
	if (type == EntityType::Bullet)
		return static_cast<float>(g_Config.game.bullet.collisionRadius);

	if (type == EntityType::Enemy)
		return static_cast<float>(g_Config.game.enemy.collisionRadius);

	if (type == EntityType::Player)
		return static_cast<float>(g_Config.game.player.collisionRadius);

	if (type == EntityType::None)
		return 0.0f;
}


int entity::getVertices() const
{
	return sides;
}

vec2 entity::getVelocity() const
{
	return velocity;
}

float entity::getSize() const
{
	return size;
}

float entity::getSpeed() const
{
	return speed;
}

void entity::setType(EntityType entType)
{
	type = entType;
}

void entity::setPos(vec2 entPos)
{
	pos = entPos;
}

void entity::setLifetime(float life)
{
	lifetime = life;
}

float entity::getAge() const
{
	return age;
}

float entity::getLifetime() const
{
	return lifetime;
}