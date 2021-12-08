#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../Component.h"

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent : public Component
{
	public:
		ProjectileEmitterComponent(int speed, int angleDeg, int range, bool isLooping)
		{
			this->speed = speed;
			this->range = range;
			this->isLooping = isLooping;
			this->angleRad = glm::radians(static_cast<float>(angleDeg)); 
		}

		void Initialize() override
		{
			transform = owner->GetComponent<TransformComponent>();
			origin = glm::vec2(transform->position.x, transform->position.y);
			transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
		}

		void Update(float deltaTime) override
		{
			if (glm::distance(transform->position, origin) > range)
			{
				if (isLooping)
				{
					transform->position.x = origin.x;
					transform->position.y = origin.y;
				}
				else
				{
					owner->Destroy();
				}
			}
		}

	private:
		TransformComponent *transform = nullptr;
		glm::vec2 origin = glm::vec2(0.f, 0.f);
		int speed = 0;
		int range = 0;
		float angleRad = 0.0f;
		bool isLooping = false;
};

#endif