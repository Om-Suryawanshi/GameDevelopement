#pragma once
#include "entity.h"


#include <random>
#include <ctime>

#include "../engine/config/config.hpp"


class Enemy : public entity
{
protected:
	float angle;
	bool is_HitbyBullet = false;

public:
	sf::CircleShape enemy;
	Enemy(int id, float speed, float size, float sides, EntityType type);
	void update();
	//bool colide(vec2& playerPos);
	void draw(sf::RenderWindow& window);
	vec2 getPos() const;
	void die();
	void rotate();
};

