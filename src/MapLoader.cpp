#include "../include/MapLoader.hpp"

MapLoader::MapLoader(Settings *settings) : _settings(settings)
{
	// enemy("enemy", "Bomberman/resources/models/bomber/untitled", 20, "Bomberman/resources/models/GoatBB/GoatBB.obj"),
	// player("player", "Bomberman/resources/models/bomber/untitled", 20), wall("wall", "Bomberman/resources/models/bomberman/cube.obj", 1, "Bomberman/resources/models/bomberman/cube.obj") {

	// renderer = &Renderer::getInstance("BombermanTestV1", 0, 0, 1.2f);

	// Image startScreenTexture("Bomberman/resources/images/bom.png");
	// renderer->generateTexture("startScreen", startScreenTexture);

	// Image groundTexture("Bomberman/resources/images/floor.png");
	// renderer->generateTexture("ground", groundTexture);

	// Image cubeTexture("Bomberman/resources/images/floor.png");
	// renderer->generateTexture("cube", cubeTexture);

	// Image skyTexture("Bomberman/resources/images/sky.png");
	// renderer->generateTexture("sky", skyTexture);

	// Image enemyTexture("Bomberman/resources/models/Goat/goat.png");
	// renderer->generateTexture("enemyTexture", enemyTexture);

	// Image treeTexture("Bomberman/resources/models/Tree/tree.png");
	// renderer->generateTexture("treeTexture", treeTexture);
}

// MapLoader::~MapLoader()
// {

// }

void MapLoader::load_map(int level)
{
	std::string		mapname("../maps/1.txt");
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

	if (_player.size() != 1 || _enemies.empty())
	{
		std::cout << "ERROR: Too Many Players/Not Enough Enemies" << std::endl;
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
			gameEngine::SceneObject temp("wall", "../resources/models/bomberman/cube.obj", 1, "../resources/models/bomberman/cube.obj");
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_walls.push_back(temp);
			break;
		}
		case 'o' :
		{
			gameEngine::SceneObject temp("wall", "../resources/models/bomberman/cube.obj", 1, "../resources/models/bomberman/cube.obj");
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_obstacles.push_back(temp);
			break;
		}
		case 'p' :
		{
			gameEngine::SceneObject temp("enemy", "../resources/models/bomber/untitled", 20, "../resources/models/bomberBB/bomberBB.obj");
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			temp.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			_player.push_back(temp);
			break;
		}
		case 'e' :
		{
			Enemy temp("enemy", "../resources/models/bomber/untitled", _settings, 20, "../resources/models/bomberBB/bomberBB.obj");
			temp.offset = glm::vec3(-11 + x_coord, _settings->GROUND_Y, -7 + y_coord);
			_enemies.push_back(temp);
			break;
		}
		default :
		{
			std::cout << "ERROR: unrecognized map token: " << type_char << std::endl;
			exit(1);
		}
	}
}
