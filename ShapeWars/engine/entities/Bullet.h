#pragma once
#include "entity.h"
#include <math.h>
#include "../engine/config/config.h"


class Bullet : public entity
{
private:
	vec2 velocity;
	float lifetime;
	float age;
	vec2 direction;

public:
	sf::CircleShape bullet;

	Bullet(int id, vec2& startPos, vec2& direction);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	vec2 getPos() const;
	//bool colide(vec2& pos);
	void die();
};