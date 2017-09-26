//
// Created by Gregory HAVENGA on 2017/09/22.
//

#include "../include/Enemy.hpp"

Enemy::Enemy(const std::string name, const std::string modelPath, Settings *settings, const int numFrames,
			 const std::string boundingBoxSetPath) :
		SceneObject(name, modelPath, numFrames, boundingBoxSetPath), _settings(settings)
{
	enemyState = WALKING_STRAIGHT;

	startAnimating();
};

void Enemy::move(float player_x, float player_z)
{
	enemyState = TURNING;

	float xDistance = player_x - offset.x;
	float zDistance = player_z - offset.z;
	float distance = sqrt(xDistance * xDistance + zDistance * zDistance);

	float enemyRelX = xDistance / distance;
	float enemyRelZ = zDistance / distance;

	float enemyDirectionX = -sin(rotation.y);
	float enemyDirectionZ = cos(rotation.y);

	float dotPosDir = enemyRelX * enemyDirectionX + enemyRelZ * enemyDirectionZ; // dot product

	if (dotPosDir > 0.98f)
		enemyState = TURNING;
	else
		enemyState = WALKING_STRAIGHT;

	if (enemyState == TURNING)
		rotation.y -= _settings->ENEMY_ROTATION_SPEED;

	if (offset.z > _settings->MAX_Z)
	{
		offset.z = _settings->MAX_Z;
		enemyState = TURNING;
	}
	if (offset.z < _settings->MIN_Z)
	{
		offset.z = _settings->MIN_Z;
		enemyState = TURNING;
	}
	if(offset.x > _settings->MAX_X)
	{
		offset.x = _settings->MAX_X;
		enemyState = TURNING;
	}
	if (offset.x < _settings->MIN_X)
	{
		offset.x = _settings->MIN_X;
		enemyState = TURNING;
	}

	offset.x += sin(rotation.y) * _settings->ENEMY_SPEED;
	offset.z -= cos(rotation.y) * _settings->ENEMY_SPEED;
	offset.y -= sin(rotation.x) * _settings->ENEMY_SPEED;

	animate();
}