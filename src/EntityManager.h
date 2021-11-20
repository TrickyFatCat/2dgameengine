#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "./Entity.h"
#include "./Component.h"

class EntityManager
{
	public:
		void Update(float deltaTime);
		void Render();
		bool HasNoEntities();
		Entity& AddEntity(std::string EntityName);
		std::vector<Entity*> GetEntities() const;
		unsigned int GetEntityCount();

	private:
		std::vector<Entity*> entities;
};

#endif