#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

namespace
{
	constexpr unsigned int WINDOW_WIDTH = 800;
	constexpr unsigned int WINDOW_HEIGHT = 600;

	constexpr unsigned int FPS = 60;
	constexpr unsigned int FRAME_TARGET_TIME = 1000 / FPS;
	constexpr float DELTA_TIME_MAX = 0.05f;

	constexpr unsigned int NUM_LAYERS = 7;

	constexpr SDL_Color WHITE_COLOR = {255, 255, 255, 255};
	constexpr SDL_Color GREEN_COLOR = {0, 255, 0, 255};
}

enum LayerType
{
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	OBSTACLE_LAYER = 3,
	PLAYER_LAYER = 4,
	PROJECTILE_LAYER = 5,
	UI_LAYER = 6
};

enum CollisionType
{
	NO_COLLISION,
	PLAYER_X_ENEMY,
	PLAYER_X_PROJECTILE,
	ENEMY_X_PROJECTILE,
	PLAYER_X_VEGETATION,
	PLAYER_X_FINISH
};

#endif