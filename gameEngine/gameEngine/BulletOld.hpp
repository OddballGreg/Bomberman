#pragma once

#include <glm/glm.hpp>
#include "SpriteBatch.hpp"

class Bullet {
	public:
		Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime);
		~Bullet();

		// void	init(glm::vec2 pos, glm::vec2 dir, float speed), int lifetime;
		void		draw(gameEngine::SpriteBatch& spriteBatch);
		bool		update();

	private:
		float		_damage;
		float		_speed;
		int			_lifetime;
		glm::vec2	_direction;
		glm::vec2	_position;
};