#include "./Game.h"

#include <iostream>

#include "./Constants.h"

Game::Game()
{
	isRunning = false;
}

Game::~Game()
{

}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 50.0f;
float projectileVelY = 50.0f;

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

	isRunning = true;
}