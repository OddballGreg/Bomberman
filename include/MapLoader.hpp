#pragma once

#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Enemy.hpp"
#include "../include/Settings.hpp"
//#include "../gameEngine/include/Renderer.hpp"
//#include "../gameEngine/include/Sound.hpp"

#include <fstream>
#include <vector>
#include <iostream>

class Enemy;

class MapLoader
{
	public:
	MapLoader(Settings *settings);
	MapLoader(MapLoader &obj) = default;
	~MapLoader() = default;

	MapLoader &operator = (MapLoader &obj) = default;

	void load_map(int level);
	void spawn_object(char type_char, float x_coord, float y_coord);

	std::vector<Enemy> _enemies;
	std::vector<gameEngine::SceneObject> _walls;
	std::vector<gameEngine::SceneObject> _obstacles;
	std::vector<gameEngine::SceneObject> _player;

	Settings *_settings;

	private:

	Enemy 					*enemy_template;
	gameEngine::SceneObject *wall_template;
	gameEngine::SceneObject *obstacle_template;
	gameEngine::SceneObject *player_template;

};

