#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "./Entity.h"
#include "./Component.h"
#include "./Constants.h"

class EntityManager
{
	public:
		void ClearData();
		void Update(float deltaTime);
		void Render();
		bool HasNoEntities() const;
		Entity& AddEntity(const std::string entityName, const LayerType layer);
		std::vector<Entity*> GetEntities() const;
		std::vector<Entity*> GetEntitiesByLayer(const LayerType layer) const;
		unsigned int GetEntityCount() const;
		std::string CheckEntityCollisions(Entity& targetEntity) const;

	private:
		std::vector<Entity*> entities;
		void ListAllEntities() const;
};

#endif