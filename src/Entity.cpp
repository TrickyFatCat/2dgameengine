#include "./Entity.h"
#include "./Component.h"

Entity::Entity(EntityManager& manager) : manager(manager)
{
	isActive = true;

}

Entity::Entity(EntityManager& manager, std::string name) : manager(manager), name(name)
{
	this->isActive = true;
}

void Entity::Update(float deltaTmie)
{
	for (auto& component : components)
	{
		component->Update(deltaTmie);
	}
}

void Entity::Render()
{
	for (auto& component : components)
	{
		component->Render();
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}

bool Entity::GetIsActive() const
{
	return this->isActive;
}