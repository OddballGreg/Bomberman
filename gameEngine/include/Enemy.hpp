//
// Created by Gregory HAVENGA on 2017/09/22.
//

#ifndef BOMBERMAN_ENEMY_H
#define BOMBERMAN_ENEMY_H

#include "../include/SceneObject.hpp"
#include "../include/Settings.hpp"
#include "../include/MapLoader.hpp"

class MapLoader;

class Enemy : public gameEngine::SceneObject
{
public:
	Enemy(const std::string name, const std::string, Settings *settings, const int numFrames = 1,
				 const std::string boundingBoxSetPath = "");
	Enemy(const Enemy &obj) = default;
	~Enemy() = default;

	Enemy &operator = (const Enemy &obj) = default;

	void move(MapLoader *maploader, int me);

	enum EnemyState {
		TURNING,
		WALKING_STRAIGHT
	};

	EnemyState enemyState;

private:

	Settings *_settings;
};


#endif //BOMBERMAN_ENEMY_H
