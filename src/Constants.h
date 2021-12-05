#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace
{
	constexpr unsigned int WINDOW_WIDTH = 800;
	constexpr unsigned int WINDOW_HEIGHT = 600;

	constexpr unsigned int FPS = 60;
	constexpr unsigned int FRAME_TARGET_TIME = 1000 / FPS;
	constexpr float DELTA_TIME_MAX = 0.05f;

	constexpr unsigned int NUM_LAYERS = 6;
}

enum LayerType
{
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	PLAYER_LAYER = 3,
	PROJECTILE_LAYER = 4,
	UI_LAYER = 5
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