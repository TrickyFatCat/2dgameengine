#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../src/TextureManager.h"
#include "../src/AssetManager.h"
#include "./TransformComponent.h"

class SpriteComponent : public Component
{
	public:
		SpriteComponent(const char* filePath){ SetTexture(filePath); };

		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
		void SetTexture(std::string assetTextureId) { texture = Game::assetManager->GetTexture(assetTextureId); }
		
		void Initialize() override
		{
			transform = owner->GetComponent<TransformComponent>();
			sourceRectangle.x = 0;
			sourceRectangle.y = 0;
			sourceRectangle.w = transform->width;
			sourceRectangle.h = transform->height;
		}

		void Update(float deltaTime) override
		{
			destinationRectangle.x = static_cast<int>(transform->position.x);
			destinationRectangle.y = static_cast<int>(transform->position.y);
			destinationRectangle.w = transform->width * transform->scale;
			destinationRectangle.h = transform->height * transform->scale;
		}

		void Render() override
		{
			TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
		}

	private:
		TransformComponent* transform = nullptr;
		SDL_Texture* texture = nullptr;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
};

#endif