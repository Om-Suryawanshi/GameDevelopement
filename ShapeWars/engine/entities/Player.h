#pragma once
#include "SFML//Graphics.hpp"
#include "../engine/config/vec2.h"
#include "../engine/config/config.h"
#include "entity.h"

class Player : public entity
{

public:
	sf::CircleShape player;

	Player(int id);
	void update();
	void draw(sf::RenderWindow& window);
	vec2 getPos() const;
};

