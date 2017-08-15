#pragma once

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Bullet.hpp"

class Gun {
	public:

		Gun(std::string name,
			int fireRate,
			int bulletsPerShot,
			float spread,
			float bulletDamage,
			float bulletSpeed,
			int lifeTime);

		~Gun();

		void update(bool isMouseDown,
					const glm::vec2& position,
					const glm::vec2& direction,
					std::vector<Bullet>& bullets);

	private:

		void fire(const glm::vec2& direction,
					const glm::vec2& position,
					std::vector<Bullet>& bullets);

		std::string _name;
		int			_fireRate;
		int			_bulletsPerShot;
		float		_spread;

		float		_bulletDamage;
		float		_bulletSpeed;

		int			_lifeTime;
		int			_frameCounter;

};