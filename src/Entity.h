#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

class EntityManager;
class Component;

class Entity
{
	public:
		std::string name;
		Entity(EntityManager& manager);
		Entity(EntityManager& manager, std::string name);

		void Update(float deltaTime);
		void Render();
		void Destroy();

		bool GetIsActive() const;

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			T* newComponent(new T(std::forward<TArgs>(args)...));
			newComponent->owner = this;
			components.emplace_back(newComponent);
			newComponent->Initialize();
			return *newComponent;
		}

	private:
		EntityManager& manager;
		bool isActive = false;
		std::vector<Component*> components;
};

#endif