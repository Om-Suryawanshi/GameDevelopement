#pragma once
#include "SFML/Graphics.hpp"
#include "../engine/config/vec2.h"

enum class EntityType 
{
	None,
	Player,
	Enemy,
	Bullet
};

class entity
{
protected:
	bool isAlive;
	int id;
	vec2 pos;
	float speed;
	float size; // Radius
	int sides;
	EntityType type = EntityType::None;

public:
	entity();
	explicit entity(int id, float speed, float size, float sides): id(id), speed(speed), size(size), sides(sides) {}
	virtual ~entity() = default;

	EntityType getType() const { return type; }
	int getId() const { return id; }
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	vec2 getPos() const;
};

