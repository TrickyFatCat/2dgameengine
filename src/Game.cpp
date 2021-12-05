#include "./Game.h"

#include <iostream>

#include "./Constants.h"
#include "../lib/glm/glm.hpp"
#include "./Components/TransformComponent.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Map.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer*  Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

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

	if (TTF_Init() != 0)
	{
		std::cerr << "Error initializing SDL_ttf." << std::endl;
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

	HandleCameraMovement();
	CheckCollisions();
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

Entity& player(manager.AddEntity("player", PLAYER_LAYER));

void Game::LoadLevel(const int levelIndex)
{
	// Start including new assets to the assetManager list
	assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
	assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
	assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);
	
	// Start including entities and also components to them
	player.AddComponent<TransformComponent>(64, 64, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<KeyboardControlComponent>("up", "down", "right", "left", "space");
	player.AddComponent<ColliderComponent>("PLAYER", 64, 64, 32, 32);

	Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
	tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	tankEntity.AddComponent<ColliderComponent>("ENEMY", 0, 0, 32, 32);

	Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
	heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
	heliport.AddComponent<SpriteComponent>("heliport-image");
	heliport.AddComponent<ColliderComponent>("FINISH", 470, 420, 32, 32);

	Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
	labelLevelName.AddComponent<TextLabelComponent>(256, 256, "First level...", "charriot-font", WHITE_COLOR);
}

void Game::HandleCameraMovement()
{
	TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	// Clamping camera position to map boundaries.

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;

	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
	switch (manager.CheckCollisions())
	{
	case PLAYER_X_ENEMY:
		ProcessGameOver();
		break;

	case PLAYER_X_PROJECTILE:
		break;

	case PLAYER_X_VEGETATION:
		break;

	case PLAYER_X_FINISH:
		ProcessNextLevel(1);
		break;

	case ENEMY_X_PROJECTILE:
		break;
	
	default:
		break;
	}
}

void Game::ProcessNextLevel(const int index)
{
	std::cout << "Next Level" << std::endl;
	isRunning = false;
}

void Game::ProcessGameOver()
{
	std::cout << "Game Over" << std::endl;
	isRunning = false;
}