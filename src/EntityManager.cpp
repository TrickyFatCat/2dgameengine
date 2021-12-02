#include "./EntityManager.h"
#include "./Entity.h"
#include "./Constants.h"

#include <iostream>

void EntityManager::ClearData()
{
	for (auto &entity : entities)
	{
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; ++layerNumber)
	{
		for (const auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
		{
			entity->Render();
		}
	}
}

bool EntityManager::HasNoEntities() const
{
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(const std::string entityName, const LayerType layer)
{
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(const LayerType layer) const
{
	std::vector<Entity*> selectedEntities;

	for (const auto& entity : entities)
	{
		if (entity->layer == layer)
		{
			selectedEntities.emplace_back(entity);
		}
	}

	return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() const
{
	return entities.size();
}

void EntityManager::ListAllEntities() const
{
	unsigned int i = 0;

	for (auto& entity : entities)
	{
		std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}
}