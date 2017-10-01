//
// Created by Gregory HAVENGA on 2017/09/22.
//

#include "../include/Enemy.hpp"

/*
+** Constructors
+*/
Enemy::Enemy(const std::string name, const std::string modelPath, Settings *settings, const int numFrames,
		const std::string boundingBoxSetPath) :
		SceneObject(name, modelPath, numFrames, boundingBoxSetPath), _settings(settings)
{
	enemyState = WALKING_STRAIGHT;

	startAnimating();
}

void Enemy::move(MapLoader *maploader, int me)
{
	glm::vec3 temp = offset;
	double orient = 0;
	static int	t, dir;

	// if (maploader->_player[0].offset.z > offset.z) {
	// 	temp.z += _settings->ENEMY_SPEED;
	// 	orient = M_PI;
	// }
	// if (maploader->_player[0].offset.z < offset.z) {
	// 	temp.z -= _settings->ENEMY_SPEED;
	// 	orient = 0;
	// }
	// if (maploader->_player[0].offset.x > offset.x) {
	// 	temp.x += _settings->ENEMY_SPEED;
	// 	orient = M_PI / 2;
	// }
	// if (maploader->_player[0].offset.x < offset.x) {
	// 	temp.x -= _settings->ENEMY_SPEED;
	// 	orient = 3 * (M_PI / 2);
	// }

	if (!t) {
		t = 100;
		dir = rand() % 4;
	}

	t--;

	if (dir == 0) {
		temp.x += _settings->ENEMY_SPEED;
		orient = M_PI / 2;
	}
	else if (dir == 1) {
		orient = 3 * (M_PI / 2);
		temp.x -= _settings->ENEMY_SPEED;
	}
	else if (dir == 2) {
		orient = M_PI;
		temp.z += _settings->ENEMY_SPEED;
	}
	else {
		orient = 0;
		temp.z -= _settings->ENEMY_SPEED;
	}

	bool collision = false;
	for(int i = maploader->_walls.size() -1; i > -1; i--)
		if (temp.z < maploader->_walls[i].offset.z + _settings->COLLISION_ZONE
			&& temp.z > maploader->_walls[i].offset.z - _settings->COLLISION_ZONE
			&& temp.x < maploader->_walls[i].offset.x + _settings->COLLISION_ZONE
			&& temp.x > maploader->_walls[i].offset.x - _settings->COLLISION_ZONE)
			collision = true;

	for(int i = maploader->_obstacles.size() -1; i > -1; i--)
		if (temp.z < maploader->_obstacles[i].offset.z + _settings->COLLISION_ZONE
			&& temp.z > maploader->_obstacles[i].offset.z - _settings->COLLISION_ZONE
			&& temp.x < maploader->_obstacles[i].offset.x + _settings->COLLISION_ZONE
			&& temp.x > maploader->_obstacles[i].offset.x - _settings->COLLISION_ZONE)
			collision = true;

	for(int i = maploader->_enemies.size() -1; i > -1; i--)
		if (temp.z < maploader->_enemies[i].offset.z + _settings->COLLISION_ZONE
			&& temp.z > maploader->_enemies[i].offset.z - _settings->COLLISION_ZONE
			&& temp.x < maploader->_enemies[i].offset.x + _settings->COLLISION_ZONE
			&& temp.x > maploader->_enemies[i].offset.x - _settings->COLLISION_ZONE
			&& i != me)
			collision = true;

	if (collision == false) {
		offset = temp;
		animate();
	}
	rotation.y = orient;
}