#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "./Entity.h"
#include "./Component.h"
#include "./Constants.h"

class ColliderComponent;

class EntityManager
{
	public:
		void ClearData();
		void Update(float deltaTime);
		void DestroyInaciveEntities();
		void Render();
		bool HasNoEntities() const;
		Entity& AddEntity(const std::string entityName, const LayerType layer);
		std::vector<Entity*> GetEntities() const;
		std::vector<Entity*> GetEntitiesByLayer(const LayerType layer) const;
		Entity* GetEntityByName(const std::string name) const;
		unsigned int GetEntityCount() const;
		CollisionType CheckCollisions() const;

	private:
		std::vector<Entity*> entities;
		void ListAllEntities() const;
		bool IsTagEqual(const ColliderComponent& collider, const std::string& colliderTag) const;
};

#endif