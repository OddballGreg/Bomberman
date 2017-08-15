#include "Level.hpp"
#include "gameEngine/ResourceManager.hpp"
#include "gameEngine/Vertex.hpp"

#include <fstream>
#include <iostream>

Level::Level(){

}

Level::~Level() {

}

Level::Level(const std::string& fileName) {

	std::ifstream file;
	file.open(fileName);

	if (file.fail()) {
		std::cout << "Failed to open " << fileName << std::endl;
	}

	std::string tmp;
	file >> tmp >> _numHumans;

	std::getline(file, tmp); // get rid of the rest of the first line

	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}
	// test to see if level was parsed
	// for (int i = 0; i < _levelData.size(); i++) {
	//	 std::cout << _levelData[i] << std::endl;
	// }
	_spriteBatch.init();

	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	gameEngine::Colour whiteColour;

	whiteColour.r = 255;
	whiteColour.g = 255;
	whiteColour.b = 255;
	whiteColour.a = 255;

	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			char tile = _levelData[y][x];
		glm::vec4   destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile)
			{
				case 'R':
					_spriteBatch.draw(destRect,
										uvRect,
										gameEngine::ResourceManager::getTexture("Textures/red_bricks.png").id,
										0.0f,
										whiteColour);
					break ;

				case 'B':
					_spriteBatch.draw(destRect,
									  uvRect,
									  gameEngine::ResourceManager::getTexture("Textures/light_bricks.png").id,
									  0.0f,
									  whiteColour);
					break ;

				case 'G':
					_spriteBatch.draw(destRect,
										uvRect,
										gameEngine::ResourceManager::getTexture("Textures/glass.png").id,
										0.0f,
										whiteColour);
					break ;

				case 'L':
					_spriteBatch.draw(destRect,
										uvRect,
										gameEngine::ResourceManager::getTexture("Textures/light_bricks.png").id,
										0.0f,
										whiteColour);
					break ;

				case '@':
					_levelData[y][x] = '.';
					_startPlayerPos.x = x * TILE_WIDTH;
					_startPlayerPos.y = y * TILE_WIDTH;
					break ;

				case 'Z':
					_levelData[y][x] = '.';
					_zombiesStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					break ;

				case '.':
					break ;

				default:
					// std::cout << "Unknown symbol " << std::endl;
					// std::cout << tile << " at " << x << " : " << y << std::endl;
					break ;
			}
		}
	}

	_spriteBatch.end();
}

void		Level::draw() {
	_spriteBatch.renderBatch();
}

int			Level::getNumHumans() const {
	return _numHumans;
}

int			Level::getWidth() const {
	return _levelData[0].size();
}

int			Level::getHeight() const {
	return _levelData.size();
}

glm::vec2	Level::getStartPlayerPos() const {
	return _startPlayerPos;
}

const		std::vector<glm::vec2>& Level::getZombieStartPositions() {
	return _zombiesStartPositions;
}

const		std::vector<std::string>& Level::getLevelData() const {
	return _levelData;
}
