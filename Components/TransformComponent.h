#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "src/Component.h"

#include "src/EntityManager.h"
#include "lib/glm/glm.hpp"

#include <SDL2/SDL.h>
#include "src/Game.h"

class TransformComponent : public Component
{
	public:
		glm::vec2 position = glm::vec2(0.0f, 0.0f);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);

		int width = 1;
		int height = 1;
		int scale = 1;

		TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
		{
			position = glm::vec2(posX, posY);
			velocity = glm::vec2(velX, velY);
			width = w;
			height = h;
			scale = s;
		}

		void Initialize() override 
		{

		};

		void Update(float deltaTime) override
		{
			position.x += velocity.x * deltaTime;
			position.y += velocity.y * deltaTime;
		};

		void Render() override
		{
			SDL_Rect transformRectangle = { static_cast<int>(position.x),
											static_cast<int>(position.y),
											width,
											height};
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(Game::renderer, &transformRectangle);
		};

	private:
};

#endif