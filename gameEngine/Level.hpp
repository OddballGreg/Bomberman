#pragma once

#include <string>
#include <vector>
#include "gameEngine/SpriteBatch.hpp"

const int TILE_WIDTH = 64;

class Level {
	public:
		// load the level from file
		Level();
		Level(const std::string& fileName);
		~Level();

		void draw();

		int getNumHumans() const;
		int getWidth() const;
		int getHeight() const;

		const std::vector<std::string>& getLevelData() const;
		glm::vec2 getStartPlayerPos () const;
		const std::vector<glm::vec2>& getZombieStartPositions();

	private:
		std::vector<std::string>	_levelData;
		int							_numHumans;
		gameEngine::SpriteBatch		_spriteBatch;

		glm::vec2					_startPlayerPos;
		std::vector<glm::vec2>		_zombiesStartPositions;

};