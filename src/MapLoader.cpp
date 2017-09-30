#include "../include/MapLoader.hpp"

MapLoader::MapLoader(Settings *settings) : _settings(settings)
{
	_enemy_template 		= new Enemy("enemy", "../resources/models/bomber/untitled", _settings, 20, "../resources/models/bomberBB/bomberBB.obj");
	_wall_template 			= new gameEngine::SceneObject("wall", "../resources/models/bomberman/cube.obj", 1, "../resources/models/bomberman/cube.obj");;
	_obstacle_template 		= new gameEngine::SceneObject("wall", "../resources/models/bomberman/cube.obj", 1, "../resources/models/bomberman/cube.obj");;
	_player_template 		= new gameEngine::SceneObject("enemy", "../resources/models/bomber/untitled", 20, "../resources/models/bomberBB/bomberBB.obj");
	_portal_open_template 	= new gameEngine::SceneObject("wall", "../resources/models/Portal/Portal_Open.obj", 1, "../resources/models/Portal/Portal_Open.obj");
	_portal_closed_template = new gameEngine::SceneObject("wall", "../resources/models/Portal/Portal_Closed.obj", 1, "../resources/models/Portal/Portal_Closed.obj");
	_powerup_template 		= new gameEngine::SceneObject("wall", "../resources/models/bomberman/power_up.obj", 1, "../resources/models/bomberman/power_up.obj");
	_explosion_template		= new gameEngine::SceneObject("wall", "../resources/models/bomberman/sphere.obj", 1, "../resources/models/bomberman/sphere.obj");
}

 MapLoader::~MapLoader()
 {
	 delete _enemy_template;
	 delete _wall_template;
	 delete _obstacle_template;
	 delete _player_template;
	 delete _portal_closed_template;
	 delete _portal_open_template;
	 delete _powerup_template;
	 delete _explosion_template;
 }

void MapLoader::load_map(int level)
{
	//Wipe Vectors Before Loading
	_enemies.clear();
	_player.clear();
	_walls.clear();
	_obstacles.clear();
	_portal.clear();
	_powerups.clear();
	_explosion.clear();

	std::string		mapname("../maps/" + std::to_string(level) + ".txt");
	std::ifstream	mapfile(mapname);
	std::string		line;
	int y = -1;

	if (!mapfile.is_open())
	{
		std::cout << "ERROR: Could not open: " << mapname << " -- Mapfile is missing or broken." << std::endl;
		exit(1);
	}

	while(std::getline(mapfile, line))
	{
		y++; // Increment line index

		int x = -1;
		// std::cout << line << std::endl;
		while (line[++x])
			spawn_object(line[x], x, y);
	}

	if (_player.size() != 1 || _enemies.empty() || _portal.size() != 2)
	{
		std::cout << "ERROR: Too Many Players/Not Enough Enemies/Odd Number Portals" << std::endl;
		exit(1);
	}

	std::cout << "Players: " << _player.size() << " Walls: " << _walls.size() << " Obstacles: " << _obstacles.size() << " Enemies: " << _enemies.size() << std::endl;
}

void MapLoader::spawn_object(char type_char, float x_coord, float y_coord)
{
	switch (type_char)
	{
		// std::cout << type_char << std::endl;
		case '.' :
			break;
		case 'w' :
		{
			gameEngine::SceneObject temp(*_wall_template);
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_walls.push_back(temp);
			break;
		}
		case 'o' :
		{
			gameEngine::SceneObject temp(*_obstacle_template);
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_obstacles.push_back(temp);
			break;
		}
		case 'p' :
		{
			gameEngine::SceneObject temp(*_player_template);
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			temp.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			_player.push_back(temp);
			break;
		}
		case 'e' :
		{
			Enemy temp(*_enemy_template);
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_enemies.push_back(temp);
			break;
		}
		case 'x' :
		{
			gameEngine::SceneObject temp(*_portal_open_template);
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_portal.push_back(temp);
			gameEngine::SceneObject temp2(*_portal_closed_template);
			temp2.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_portal.push_back(temp2);
			gameEngine::SceneObject temp3(*_obstacle_template);
			temp3.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_obstacles.push_back(temp3);
			break;
		}
		default :
		{
			std::cout << "ERROR: unrecognized map token: " << type_char << std::endl;
			exit(1);
		}
	}
}
