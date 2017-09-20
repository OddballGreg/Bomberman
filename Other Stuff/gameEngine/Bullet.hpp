#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "gameEngine/SpriteBatch.hpp"
#include "Agent.hpp"
#include "Level.hpp"

class Human;
class Zombie;

class Bullet {

	public:

		Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed, int lifeTime);
		~Bullet();

		// void	init(glm::vec2 pos, glm::vec2 dir, float speed), int lifetime;
		void	draw(gameEngine::SpriteBatch& spriteBatch);
		bool	update(const std::vector<std::string>& levelData);
		bool	collideWithAgent(Agent* agent);
		float	getDamage() const;

	private:

		bool		collideWithWorld(const std::vector<std::string>& levelData);
		int			_lifeTime;
		float		_speed;
		float		_damage;
		glm::vec2	_direction;
		glm::vec2	_position;
};