#include "./EntityManager.h"
#include "./Entity.h"
#include "./Constants.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

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

CollisionType EntityManager::CheckCollisions() const
{
	for (int i = 0; i < entities.size() - 1; i++)
	{
		const auto& currentEntity = entities.at(i)
		
		if (!currentEntity->HasComponent<ColliderComponent>()) continue;
		
		ColliderComponent* currentCollider = currentEntity->GetComponent<ColliderComponent>();

		for (int j = i + 1; j < entities.size(); j++)
		{
			const auto& targetEntity = entities.at(j);

			if (!targetEntity->HasComponent<ColliderComponent>() || currentEntity->name.compare(targetEntity->name) == 0) continue;
			
			ColliderComponent* targetCollider = targetEntity->GetComponent<ColliderComponent>();

			if(Collision::CheckRectangleCollision(currentCollider->collider, targetCollider->collider))
			{
				if (IsTagEqual(*currentCollider, "PLAYER") && IsTagEqual(*targetCollider, "ENEMY"))
				{
					return PLAYER_X_ENEMY;
				}

				if (IsTagEqual(*currentCollider, "PLAYER") && IsTagEqual(*targetCollider, "PROJECTILE"))
				{
					return PLAYER_X_PROJECTILE;
				}

				if (IsTagEqual(*currentCollider, "ENEMY") && IsTagEqual(*targetCollider, "FRIENDLY_PROJECTILE"))
				{
					return ENEMY_X_PROJECTILE;
				}

				if (IsTagEqual(*currentCollider, "PLAYER") && IsTagEqual(*targetCollider, "FINISH"))
				{
					return PLAYER_X_FINISH;
				}
			}
		}
	}
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

bool EntityManager::IsTagEqual(const ColliderComponent& collider, const std::string& tag) const
{
	return collider.colliderTag.compare(tag) == 0;
}