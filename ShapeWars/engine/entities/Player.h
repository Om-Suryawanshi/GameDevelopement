#pragma once
#include "SFML//Graphics.hpp"
#include "../engine/config/vec2.h"
#include "../engine/config/config.hpp"
#include "entity.h"

class Player : public entity
{
protected:
	bool justRespawned = false;

public:
	sf::CircleShape player;

	Player(int id);
	void update();
	void draw(sf::RenderWindow& window);
	vec2 getPos() const;
	void die();
};