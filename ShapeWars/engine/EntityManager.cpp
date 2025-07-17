#include "EntityManager.h"


EntityManager::EntityManager()
	:nextId(0)
{

}

void EntityManager::markForRemoval(int id)
{
	entToRemove.push_back(id);
}

void EntityManager::destroyEnt()
{
	for (int id : entToRemove)
	{
		entities.erase(id);
	}
	entToRemove.clear();
}

void EntityManager::update()
{
	for (auto& [id, ent] : entities)
	{
		if (ent) ent->update();
		if (!ent->getisAlive())
		{
			markForRemoval(id);
		}
	}

	destroyEnt();
}

void EntityManager::draw(sf::RenderWindow& window)
{
	for (auto& [id, ent] : entities)
	{
		if (ent) ent->draw(window);
	}
}



std::shared_ptr<entity> EntityManager::getEnt(int id)
{
	auto ent = entities.find(id);
	return ent != entities.end() ? ent->second : nullptr;
}


const std::unordered_map<int, std::shared_ptr<entity>>& EntityManager::getAllEnt() const
{
	return entities;
}