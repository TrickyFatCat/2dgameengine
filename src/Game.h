#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "./EntityManager.h"

class AssetManager;

class Game
{
	public:
		Game();
		~Game();
		static SDL_Renderer* renderer;
		static AssetManager* assetManager;
		static SDL_Event event;
		static SDL_Rect camera;
		int ticksLastFrame = 0;
		void Initialize(const int width, const int height);
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();
		bool GetIsRunning() const { return isRunning; }
		void LoadLevel(const int levelIndex);
		void HandleCameraMovement();
		void CheckCollisions();

	private:
		bool isRunning = false;
		SDL_Window *window = nullptr;
};

#endif