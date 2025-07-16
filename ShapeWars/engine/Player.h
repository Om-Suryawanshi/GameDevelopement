#pragma once
#include "SFML//Graphics.hpp"
#include "config/vec2.h"
#include "config/config.h"


class Player
{
	vec2 pos;
	float speed;
	float radius;
	int sides; // Later to be implemented in config


public:
	sf::CircleShape player;
	Player();
	void update();
	void draw(sf::RenderWindow& window);
};

