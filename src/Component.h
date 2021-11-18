#ifndef COMPONENT_H
#define COMPONENT_H

class Entitiy;

class Component
{
	public:
		Entity* owner = nullptr;

		virtual ~Component() {};
		virtual void Initialize() {};
		virtual void Update(float deltaTime) {};
		virtual void Render() {};
};

#endif