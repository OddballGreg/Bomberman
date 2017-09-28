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

class MapLoader
{

	public:
	MapLoader(Settings *settings);
	~MapLoader() = default;

	void load_map(std::string mapname);
	void spawn_object(char type_char, float x_coord, float y_coord);

	std::vector<Enemy> _enemies;
	std::vector<gameEngine::SceneObject> _walls;
	std::vector<gameEngine::SceneObject> _obstacles;
	std::vector<gameEngine::SceneObject> _player;

	Settings *_settings;

	private:

};

