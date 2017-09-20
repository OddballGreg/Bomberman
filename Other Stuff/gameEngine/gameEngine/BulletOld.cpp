#include "Bullet.hpp"
#include "ResourceManager.hpp"

 Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime) {
	_position = pos;
	_direction = dir;
	_speed = speed;
	_lifetime = lifetime;
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
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static gameEngine::GLTexture texture = gameEngine::ResourceManager::getTexture("./textures/jimmyJump_pack/PNG/Bullet.png");
	gameEngine::Colour colour;
	colour.r = 255;
	colour.g = 255;
	colour.b = 255;
	colour.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, colour);
}

bool Bullet::update() {
	_position += _direction * _speed;
	_lifetime--;
	if (_lifetime == 0) {
		return true;
	}
	else
		return false;
}