#pragma once
#include "SFML/Graphics.hpp"
#include "../engine/config/vec2.h"
#include "../engine/config/config.hpp"

enum class EntityType 
{
	None,
	Player,
	Enemy,
	Bullet,
	MiniEnemy
};

class entity
{
protected:
	bool isAlive;
	int id;
	float lifetime;
	float age;
	vec2 pos;
	float speed;
	float size; // Radius
	int sides;
	bool paused = false;
	EntityType type = EntityType::None;

public:
	entity();
	explicit entity(int id, float speed, float size, float sides) : id(id), speed(speed), size(size), sides(static_cast<int>(sides)) {} // Used for player and enemy
	
	explicit entity(int id, float speed, float size, float sides, vec2& pos) : id(id), speed(speed), size(size), sides(static_cast<int>(sides)), pos(pos) {} // Used for bullet

	virtual ~entity() = default;

	EntityType getType() const { return type; }
	int getId() const { return id; }
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	vec2 getPos() const;
	void die();
	bool getisAlive() const;
	void pause();
	float getCollisionRadius() const;
	int getVertices() const;
	int getSpeed() const;
	int getSize() const;
	void setType(EntityType type);
	void setPos(vec2 pos);
	void setLifetime(int life);
};

