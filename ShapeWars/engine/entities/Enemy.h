#pragma once
#include "entity.h"


#include <random>
#include <ctime>

#include "../engine/config/config.h"


class Enemy : public entity
{
protected:
	vec2 velocity;
	float angle;

public:
	sf::CircleShape enemy;
	Enemy(int id);
	void update();
	//bool colide(vec2& playerPos);
	void draw(sf::RenderWindow& window);
	vec2 getPos() const;
	void die();
};

