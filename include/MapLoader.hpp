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
	~MapLoader();

	MapLoader &operator = (MapLoader &obj) = default;

	void load_map(int level);
	void spawn_object(char type_char, float x_coord, float y_coord);

	std::vector<Enemy> _enemies;
	std::vector<gameEngine::SceneObject> _walls;
	std::vector<gameEngine::SceneObject> _obstacles;
	std::vector<gameEngine::SceneObject> _player;
	std::vector<gameEngine::SceneObject> _portal;
	std::vector<gameEngine::SceneObject> _powerups;
	std::vector<gameEngine::SceneObject> _explosion;

	Settings *_settings;

	Enemy 					*_enemy_template;
	gameEngine::SceneObject *_wall_template;
	gameEngine::SceneObject *_obstacle_template;
	gameEngine::SceneObject *_player_template;
	gameEngine::SceneObject *_portal_open_template;
	gameEngine::SceneObject *_portal_closed_template;
	gameEngine::SceneObject *_powerup_template;
	gameEngine::SceneObject *_bomb_template;
	gameEngine::SceneObject *_explosion_template;

	private:

};

