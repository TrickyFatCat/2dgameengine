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
#include "./Components/ProjectileEmitterComponent.h"
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

	LoadLevel(1);

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

// Entity& player(manager.AddEntity("player", PLAYER_LAYER));

void Game::LoadLevel(const int levelIndex)
{
	sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string levelName = "Level" + std::to_string(levelIndex);
    lua.script_file("./scripts/" + levelName + ".lua");

    /*********************************************/
    /* LOADS ASSETS FROM LUA CONFIG FILE         */
    /*********************************************/
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];

    unsigned int assetIndex = 0;

    while (true)
	{
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];

        if (existsAssetIndexNode == sol::nullopt)
		{
            break;
        } 
		else 
		{
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];

            if (assetType.compare("texture") == 0)
			{
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str());
            }
        }
        
		assetIndex++;
    }

    /*********************************************/
    /* LOADS MAP FROM LUA CONFIG FILE            */
    /*********************************************/
    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];

    map = new Map(
        mapTextureId,
        static_cast<int>(levelMap["scale"]),
        static_cast<int>(levelMap["tileSize"])
    );

    map->LoadMap(
        mapFile,
        static_cast<int>(levelMap["mapSizeX"]),
        static_cast<int>(levelMap["mapSizeY"])
    );
}

void Game::HandleCameraMovement()
{

	// TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

	// camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	// camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

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
		ProcessGameOver();
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