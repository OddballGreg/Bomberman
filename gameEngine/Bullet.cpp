#include "Bullet.hpp"
#include "gameEngine/ResourceManager.hpp"
#include "Human.hpp"
#include "Zombie.hpp"

int BULLET_RADIUS = 15;

 Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed, int lifeTime) {
	_position = position;
	_direction = direction;
	_damage = damage;
	_speed = speed;
	_lifeTime = lifeTime;
}

Bullet::~Bullet() {

}

// void Bullet::init(glm::vec2 pos, glm::vec2 dir, float speed, int liftime) {
// 	_postion = pos;
// 	_direction = dir;
// 	_speed = speed;
// 	_lifetime = lifetime;
// }

void Bullet::draw(gameEngine::SpriteBatch& spriteBatch) {

	glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	static gameEngine::GLTexture texture = gameEngine::ResourceManager::getTexture("Textures/circle.png");
	gameEngine::Colour colour;
	colour.r = 255;
	colour.g = 255;
	colour.b = 255;
	colour.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(destRect, uvRect, texture.id, 0.0f, colour);
}

bool Bullet::update(const std::vector<std::string>& levelData) {

	// _position += _direction * _speed;

	std::cout << _lifeTime << std::endl;
	_lifeTime--;
	if (_lifeTime == 0) {
		return true;
	}

	return collideWithWorld(levelData);

	// if (_lifeTime == 0) {
	// 	return true;
	// }
	// else
	// 	return false;
}

bool Bullet::collideWithAgent(Agent* agent) {

	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData) {

	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() || gridPosition.x < 0 || gridPosition.y >= levelData.size()) {
		return true;
	}
	return (levelData[gridPosition.y][gridPosition.x] != '.');
}

float Bullet::getDamage() const {
	return _damage;
}