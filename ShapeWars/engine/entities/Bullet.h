#pragma once
#include "entity.h"
#include <math.h>
#include "../engine/config/config.hpp" //FPS


class Bullet : public entity
{
private:
	vec2 direction;

public:
	sf::CircleShape bullet;

	Bullet(int id, vec2 startPos, vec2 direction);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	vec2 getPos() const;
	void die();
};