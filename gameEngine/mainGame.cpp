#include "mainGame.h"
#include "gameEngine/gameEngine.hpp"
#include "gameEngine/SpriteBatch.hpp"
#include "gameEngine/Timing.hpp"
#include "Zombie.hpp"
#include "Gun.hpp"

#include <iostream>
#include <random>
#include <ctime>

const float HUMAN_SPEED = 2.0f;
const float ZOMBIE_SPEED = 3.5f;

MainGame::MainGame() : _width(1024), _height(768), _fps(0.0f) {

	_gameState = GameState::PLAY;
	_player = nullptr;
	_currentGunIndex = -1;
}

MainGame::~MainGame()
{
	for(int i = 0; i < _levels.size(); i++) {
		delete _levels[i];
	}
}

void MainGame::run() {
	initSystems();
	initLevel();

	gameLoop();

}

void MainGame::initSystems() {
	gameEngine::init();
	// Empty
	_window.create(_width, _height, "bomber");
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	initShaders();
	_agentSpriteBatch.init();
	_camera.init(_width, _height);

}

void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(4.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);
	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	// set up humans and draw

	for (int i = 0; i < 10; i++) {
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	}

	// // add zombies to the equation
	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();

	for (int i = 0; i < zombiePositions.size(); i++) {
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	// _player->addGun(new Gun("pistol", 30, 1, 10.0f, 30, 10.0f, 80));
	// _player->addGun(new Gun("shotgun", 60, 20, 40.0f, 4, 20.0f, 50));
	// _player->addGun(new Gun("mp5", 5, 1, 20.0f, 20, 10.0f, 20));
}

void MainGame::initShaders() {
	// Compile our color shader
	_textureProgram.compileShaders("colourshading.vert", "colourshading.frag");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void MainGame::gameLoop() {
	// Empty

	// gameEngine::FpsLimiter fpsLimiter;
	// fpsLimiter.setMaxFPS(60.0f);

	while (_gameState == GameState::PLAY) {
		// fpsLimiter.beginFrame();

		processInput();
		drawGame();

		// _fps = fpsLimiter.end();
	}
}

void MainGame::updateAgents() {
	// updates all humans
	for (int i = 0; i <_humans.size(); i++) {
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}

	// updates all zombies
	for (int i = 0; i <_zombies.size(); i++) {
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}

	// update zombie collisions

	for (int i = 0; i < _zombies.size(); i++) {
		for (int j = i + 1; j < _zombies.size(); j++) {
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
		for (int j = 1; j < _humans.size(); j++) {
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				// add a new zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());

				// delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
		if (_zombies[i]->collideWithAgent(_player)) {
			std::cout << "YOU LOSE, LOSER!" << std::endl;
			_gameState = GameState::EXIT;
		}
	}

	// update human collisions

	for (int i = 0; i < _humans.size(); i++) {
		for (int j = i + 1; j < _humans.size(); j++) {
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}
}

void MainGame::updateBullets() {


	// need just one bomb at a time
	for (int i = 0; i < _bullets.size();) {
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData())){
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
			i++;
	}
	for (int i = 0; i < _bullets.size(); i++) {
		for (int j = 0; j < _zombies.size();) {
			if (_bullets[i].collideWithAgent(_zombies[j])) {
				if (_zombies[j]->applyDamage(_bullets[i].getDamage())) {
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
				}
				else {
					j++;
				}
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				i--;
				break;
			}
			else {
				j++;
			}
		}
	}
}


void MainGame::processInput() {

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	glm::vec2 mouseCoords;

	glfwSetCursorPosCallback(_window.glWindow, cursorPositionCallback);
	glfwSetCursorEnterCallback(_window.glWindow, cursorEnterCallback);
	glfwSetInputMode(_window.glWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);

	_mouseLeft = glfwGetMouseButton(_window.glWindow, GLFW_MOUSE_BUTTON_LEFT);
	_mouseRight = glfwGetMouseButton(_window.glWindow, GLFW_MOUSE_BUTTON_RIGHT);


	if (glfwGetKey(_window.glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		_gameState = GameState::EXIT;
		glfwSetWindowShouldClose(_window.glWindow, GL_TRUE);
	}

	else if (glfwGetKey(_window.glWindow, GLFW_KEY_W) == GLFW_PRESS) {
		_player->pressKey(GLFW_KEY_W);
	}

	else if (glfwGetKey(_window.glWindow, GLFW_KEY_S) == GLFW_PRESS) {
		_player->pressKey(GLFW_KEY_S);
	}

	else if (glfwGetKey(_window.glWindow, GLFW_KEY_A) == GLFW_PRESS) {
		_player->pressKey(GLFW_KEY_A);
	}

	else if (glfwGetKey(_window.glWindow, GLFW_KEY_D) == GLFW_PRESS) {
		_player->pressKey(GLFW_KEY_D);
	}

	// else if (glfwGetKey(_window.glWindow, GLFW_KEY_1) == GLFW_PRESS) {
	//	 _player->pressKey(GLFW_KEY_1);
	// }

	// else if (glfwGetKey(_window.glWindow, GLFW_KEY_2) == GLFW_PRESS) {
	//	 _player->pressKey(GLFW_KEY_2);
	// }

	else if (glfwGetKey(_window.glWindow, GLFW_KEY_Q) == GLFW_PRESS)
		_camera.setScale(_camera.getScale() + SCALE_SPEED);

	else if (glfwGetKey(_window.glWindow, GLFW_KEY_E) == GLFW_PRESS)
		_camera.setScale(_camera.getScale() - SCALE_SPEED);

	if (_mouseLeft == GLFW_PRESS) {
		std::cout << "Left Press worked" << std::endl;
		glfwGetCursorPos(_window.glWindow, &_xPos, &_yPos);
		mouseCoords.x = _xPos;
		mouseCoords.y = _yPos;

		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		// std::cout << mouseCoords.x << " : " << mouseCoords.y << std::endl;
		glm::vec2 centerPosition(_player->getPosition());
		glm::vec2 direction = mouseCoords - centerPosition;
		direction = glm::normalize(direction);
		for (int i = 0; i < 1; i++) {
			_bullets.emplace_back(centerPosition, direction, 20.0f, 25.0f, 200); //200 is lifeTime of bomb
		}


	}

	if (_mouseRight == GLFW_PRESS) {
		std::cout << "Right Press worked" << std::endl;
		glfwGetCursorPos(_window.glWindow, &_xPos, &_yPos);
		mouseCoords.x = _xPos;
		mouseCoords.y = _yPos;

		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << " : " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(_player->getPosition());
		glm::vec2 direction = playerPosition;
		direction = glm::normalize(direction);
		_bullets.emplace_back(playerPosition, playerPosition, 5.0f, 10.0f, 80);
	}
}

void MainGame::drawGame() {

	gameEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);

	 while (_gameState != GameState::EXIT) {
		glfwPollEvents();

		fpsLimiter.beginFrame();

		// _time += 0.01;
		processInput();

		updateAgents();
		updateBullets();

		_camera.setPosition(_player->getPosition());
		_camera.update();

	// Set the base depth to 1.0
		glClearDepth(1.0);
	// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_textureProgram.use();

		glActiveTexture(GL_TEXTURE0);

		GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);

		glm::mat4 projectionMatrix = _camera.getCameraMatrix();

		GLint pUniform = _textureProgram.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
		_levels[_currentLevel]->draw();

		_agentSpriteBatch.begin();

		// draw player

		for (int i = 0; i < _humans.size(); i++) {
			_humans[i]->draw(_agentSpriteBatch);
		}

		for (int i = 0; i < _zombies.size(); i++) {
			_zombies[i]->draw(_agentSpriteBatch);
		}

		for (int i = 0; i < _bullets.size(); i++) {
			_bullets[i].draw(_agentSpriteBatch);
		}

		_agentSpriteBatch.end();
		_agentSpriteBatch.renderBatch();

		_textureProgram.unUse();
	//Draw code goes here

	//Swap our buffer and draw everything to the screen!
		_window.swapBuffer();
		glfwPollEvents();
		 _fps = fpsLimiter.end();
	 }
}

void MainGame::cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	// std::cout << "X: " << xPos << "Y: " << yPos << std::endl;
}

void MainGame::cursorEnterCallback(GLFWwindow *window, int entered) {
	if (entered) {
		std::cout << "cursor in window" << std:: endl;
	}
	else {
		std::cout << "left window" << std::endl;

	}
}

void MainGame::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "Left button pressed" << std::endl;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		std::cout << "Left button released" << std::endl;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "Right button pressed" << std::endl;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		std::cout << "Right button pressed" << std::endl;
}
