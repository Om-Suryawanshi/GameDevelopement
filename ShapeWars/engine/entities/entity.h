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
	vec2 velocity;
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
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	void die();
	void pause();
	// Getter
	EntityType getType() const { return type; }
	int getId() const { return id; }
	float getCollisionRadius() const;
	bool getisAlive() const;
	vec2 getPos() const;
	int getVertices() const;
	float getSpeed() const;
	float getSize() const;
	float getAge() const;
	float getLifetime() const;
	vec2 getVelocity() const;
	// Setter
	void setType(EntityType type);
	void setPos(vec2 pos);
	void setLifetime(float life);
	void setAge(float a) { age = a; }
	void setVelocity(const vec2& v) { velocity = v; }
};

