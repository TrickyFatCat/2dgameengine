#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
	public:
		Game();
		~Game();
		void Initialize(const int width, const int height);
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();
		bool GetIsRunning() const { return IsRunning; }

	private:
		bool IsRunning = false;
		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;
};

#endif