#pragma once

#ifndef MAINGAME_HPP
#define MAINGAME_HPP

#include "gameEngine.hpp"
#include "Sprite.hpp"
#include "GLSLProgram.hpp"
#include "GLTexture.hpp"
#include "Window.hpp"
#include "Camera2D.hpp"
#include "SpriteBatch.hpp"
#include "InputManager.hpp"
#include "Timing.hpp"
#include "Bullet.hpp"
#include "Bomb.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

enum class gameState {
	PLAY,
	EXIT
};

class mainGame {
	public:
		mainGame();
		~mainGame();

		void run();

	private:

		bool		initSystems();
		void		initShaders();
		// void		drawTriangle();
		void		render();
		// GLFWwindow * window;
		gameEngine::Window	  window;

		int			_width;
		int			_height;
		void		gameLoop();
		void		processInput();
		void		drawGame();
		static void	cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
		static void	cursorEnterCallback(GLFWwindow *window, int entered);
		static void	mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

		gameState	_gameState;

		gameEngine::GLSLProgram		_colourProgram;
		gameEngine::Camera2D		_camera;
		gameEngine::SpriteBatch		_spriteBatch;
		gameEngine::InputManager	_inputManager;
		gameEngine::FpsLimiter		_fpsLimiter;
		std::vector<Bullet>			_bullets;
		std::vector<Bomb>			_bombs;

		float						_time;
		float						_fps;
		float						_maxFPS;

		double						_xPos;
		double						_yPos;
		int							_mouseLeft;
		int							_mouseRight;
};

#endif