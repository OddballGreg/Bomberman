#pragma once

#include <glm/glm.hpp>
#include "SpriteBatch.hpp"

class Bomb {
	public:
		Bomb(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime);
		~Bomb();

		// void	init(glm::vec2 pos, glm::vec2 dir, float speed), int lifetime;
		void		draw(gameEngine::SpriteBatch& spriteBatch);
		bool		update();

	private:
		float		_speed;
		int			_lifetime;
		glm::vec2	_direction;
		glm::vec2	_position;
};