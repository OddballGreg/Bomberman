//
// Created by Gregory HAVENGA on 2017/09/22.
//

#include "Settings.hpp"

Settings::Settings()
{
	VERBOSE = false;

	GROUND_Y = -1.0f;
	MAX_Z = 10.0f;
	MIN_Z = -8.0f;
	MAX_X = 12.0f;
	MIN_X = -12.0f;

	ENEMY_ROTATION_SPEED = 0.1f;
	ENEMY_SPEED = 0.025f;

    PLAY_SOUND = false;
    COLLISION_ZONE = 0.8f;

	PLAYER_ROTATION_SPEED = 0.06f;
	PLAYER_SPEED = 0.08f;

	FULL_ROTATION = 6.28f; // More or less 360 degrees in radians

    BOMB_RADIUS = 1;
    BOMB_COLLUMN = 0.65;

    LEVEL_COUNT = 5;
    POWERUP_CHANCE = 50.0;
}