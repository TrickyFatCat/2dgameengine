#include "./Game.h"

#include <iostream>

#include "./Constants.h"
#include "../lib/glm/glm.hpp"
#include "./Components/TransformComponent.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer*  Game::renderer;

Game::Game()
{
	isRunning = false;
}

Game::~Game()
{

}

void Game::Initialize(const int width, const int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}

	window = SDL_CreateWindow(NULL,
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  width,
							  height,
							  SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	LoadLevel(0);

	isRunning = true;
}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
		break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
		break;

		default:
		break;
	}
}

void Game::Update()
{
	// Sleep the exectution until we reach the target frame time in milliseconds
	const int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	// Only call delay if we are too fast to process this frame
	if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}

	// Delta time is the difference in ticks from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// Clamp deltaTime to a maximum value
	deltaTime = (deltaTime > DELTA_TIME_MAX) ? DELTA_TIME_MAX : deltaTime;

	// Sets the new ticks for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();

	manager.Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	if (manager.HasNoEntities()) return;

	manager.Render();
	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::LoadLevel(const int levelIndex)
{
	// Start including new assets to the assetManager list
	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	
	// Start including entities and also components to them
	Entity& tankEntity(manager.AddEntity("tank"));
	tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");

	Entity& chopperEntity(manager.AddEntity("chopper"));
	tankEntity.AddComponent<TransformComponent>(64, 64, 0, 20, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);

	Entity& radarEntity(manager.AddEntity("radar"));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}