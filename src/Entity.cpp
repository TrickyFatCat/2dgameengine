#include "./Entity.h"
#include "./Component.h"
#include "./Constants.h"

#include <iostream>

Entity::Entity(EntityManager& manager) : manager(manager)
{
	isActive = true;

}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer) : manager(manager), name(name), layer(layer)
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

void Entity::ListAllComponents() const
{
	for (auto& mapElement : componentTypeMap)
	{
		std::cout << "Component<" << mapElement.first->name() << ">" << std::endl;
	}
}