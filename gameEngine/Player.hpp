#pragma once

#include "gameEngine/InputManager.hpp"
#include "gameEngine/Camera2D.hpp"

#if ((uname -s), Darwin) 
	#include <OpenGL/gl3.h>
#else
	#include <GLES3/gl3.h>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Human.hpp"
#include "Gun.hpp"
#include "Bullet.hpp"
// class Gun;

class Player : public Human {
	public:
		Player();
		~Player();

		void	init(int speed, glm::vec2 position, gameEngine::InputManager* inputManager, gameEngine::Camera2D* camera, std::vector<Bullet>* bullets);
		void	update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;

		void	pressKey(unsigned int keyID);
		void	releaseKey(unsigned int keyID);

		void	addGun(Gun* gun);

		static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
		static void cursorEnterCallback(GLFWwindow *window, int entered);
		static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

	private:
		gameEngine::InputManager*	_inputManager;
		gameEngine::Camera2D*		_camera;
		std::vector<Gun*>			_guns;
		std::vector<Bullet>*		_bullets;

		// int						 _currentGunIndex;

		double						_xPos;
		double						_yPos;
		int							_mouseLeft;
		int							_mouseRight;

};
