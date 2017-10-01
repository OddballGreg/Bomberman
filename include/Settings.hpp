//
// Created by Gregory HAVENGA on 2017/09/22.
//

#ifndef BOMBERMAN_SETTINGS_HPP
#define BOMBERMAN_SETTINGS_HPP

class Settings {

public:
	// Methods
	Settings();
	Settings(Settings &obj) = default;
	~Settings() = default;

	Settings &operator=(Settings &obj) = default;

	//Variables
	float	ENEMY_ROTATION_SPEED;
	float	ENEMY_SPEED;
	float	GROUND_Y;
	float	MAX_Z;
	float	MIN_Z;
	float	MAX_X;
	float	MIN_X;
	bool	PLAY_SOUND;
	float	PLAYER_ROTATION_SPEED;
	float	PLAYER_SPEED;
	float	FULL_ROTATION;
	bool	VERBOSE;
	float	COLLISION_ZONE;
	int		SCREEN_WIDTH;
	int		SCREEN_HEIGHT;
	float	BOMB_RADIUS;
	float	BOMB_COLLUMN;
	int		LEVEL_COUNT;
	float	POWERUP_CHANCE;
	int		EXPLOSION_TIME;

private:

};


#endif //BOMBERMAN_SETTINGS_HPP
