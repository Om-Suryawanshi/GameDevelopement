#pragma once
#include <memory>
#include <unordered_map>


#include "entities/entity.h"
#include "entities/Bullet.h"

#include "SFML/Graphics.hpp"

class EntityManager
{
private:
	int nextId;
	std::unordered_map<int, std::shared_ptr<entity> > entities;
	std::vector<int> entToRemove;
	void markForRemoval(int id);
	void destroyEnt();

public:
	EntityManager();
	template <typename T, typename... Args>
	std::shared_ptr<T> createEntity(Args&&... args)
	{
		auto entity = std::make_shared<T>(nextId, std::forward<Args>(args)...);
		entities[nextId] = entity;
		++nextId;
		return entity;
	}

	const std::unordered_map<int, std::shared_ptr<entity>>& getAllEnt() const;

	std::shared_ptr<entity> getEnt(int id);
	void update(); // Call update to all entities
	void draw(sf::RenderWindow& window);
};

