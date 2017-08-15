#pragma once

#include "gameEngine/Window.hpp"
#include "gameEngine/GLSLProgram.hpp"
#include "gameEngine/Camera2D.hpp"
#include "gameEngine/InputManager.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "gameEngine/Bomb.hpp"
#include "Bullet.hpp"
#include "gameEngine/SpriteBatch.hpp"

class Zombie;

enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();
	void initLevel();
	/// Initializes the shaders
	void initShaders();
	void addGun(Gun* gun);

	/// Main game loop for the program
	void gameLoop();

	void updateAgents();
	void updateBullets();

	/// Handles input processing
	void processInput();
	/// Renders the game
	void drawGame();

	static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
	static void cursorEnterCallback(GLFWwindow *window, int entered);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

private:

	std::vector<Bullet>			_bullets;
	std::vector<Bomb>			_bombs;
	int							_width;
	int							_height;

	double						_xPos;
	double						_yPos;
	int							_mouseLeft;
	int							_mouseRight;

	int							_fps;
	int							_currentLevel;
	int							_currentGunIndex;

	/// Member Variables
	gameEngine::Window			_window; ///< The game window
	gameEngine::GLSLProgram		_textureProgram; ///< The shader program
	gameEngine::InputManager	_inputManager; ///< Handles input
	gameEngine::Camera2D		_camera; ///< Main Camera

	std::vector<Level*>			_levels;
	GameState					_gameState;

	Player*						_player;
	std::vector<Human*>			_humans;
	std::vector<Zombie*>		_zombies;
	std::vector<Gun*>			_guns;
	// std::vector<Bullet>const	_bullets;

	gameEngine::SpriteBatch		_agentSpriteBatch;

};

