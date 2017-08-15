#include "mainGame.hpp"
#include "ResourceManager.hpp"
#include <SDL2/SDL.h>

#include "Log.hpp"
#include "Logger.hpp"

mainGame::mainGame() {
	// Log log("mainGame", "mainGame", CRITICAL);
	_width = 640;
	_height = 480;
	_gameState = gameState::PLAY;
	_time = 0.0f;
	_maxFPS = 60.0f;
	_camera.init(_width, _height);
	_xPos = 0;
	_yPos = 0;
	std::cout << "constructor" << std::endl;
}

mainGame::~mainGame() {
	// Log log("mainGame", "~mainGame", CRITICAL);
	std::cout << "destructor" << std::endl;
}

void mainGame::run() {
	// Log log("mainGame", "run", CRITICAL);
	initSystems();
	gameLoop();
}

bool mainGame::initSystems() {
	// Log log("mainGame", "initSystems", CRITICAL);
	gameEngine::init();
	window.create(_width, _height, "Test Window");

	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void mainGame::initShaders() {
	// Log log("mainGame", "initShaders", CRITICAL);
	_colourProgram.compileShaders("colourshading.vert", "colourshading.frag");
	_colourProgram.addAttribute("vertexPosition");
	_colourProgram.addAttribute("vertexColour");
	_colourProgram.addAttribute("vertexUV");
	_colourProgram.linkShaders();
}

void mainGame::processInput() {

	// Log log("mainGame", "processInput", CRITICAL);
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	glm::vec2 mouseCoords;

	glfwSetCursorPosCallback(window.glWindow, cursorPositionCallback);
	glfwSetCursorEnterCallback(window.glWindow, cursorEnterCallback);
	glfwSetInputMode(window.glWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);

	_mouseLeft = glfwGetMouseButton(window.glWindow, GLFW_MOUSE_BUTTON_LEFT);
	_mouseRight = glfwGetMouseButton(window.glWindow, GLFW_MOUSE_BUTTON_RIGHT);


	if (glfwGetKey(window.glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.glWindow, GL_TRUE);

	else if (glfwGetKey(window.glWindow, GLFW_KEY_W) == GLFW_PRESS)
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));

	else if (glfwGetKey(window.glWindow, GLFW_KEY_S) == GLFW_PRESS)
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));

	else if (glfwGetKey(window.glWindow, GLFW_KEY_A) == GLFW_PRESS)
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));

	else if (glfwGetKey(window.glWindow, GLFW_KEY_D) == GLFW_PRESS)
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));

	else if (glfwGetKey(window.glWindow, GLFW_KEY_Q) == GLFW_PRESS)
		_camera.setScale(_camera.getScale() + SCALE_SPEED);

	else if (glfwGetKey(window.glWindow, GLFW_KEY_E) == GLFW_PRESS)
		_camera.setScale(_camera.getScale() - SCALE_SPEED);

	if (_mouseLeft == GLFW_PRESS) {
		std::cout << "Left Press worked" << std::endl;
		glfwGetCursorPos(window.glWindow, &_xPos, &_yPos);
		mouseCoords.x = _xPos;
		mouseCoords.y = _yPos;

		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << " : " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);
		_bullets.emplace_back(playerPosition, direction, 1.0f, 1);
	}
	if (_mouseRight == GLFW_PRESS) {
		std::cout << "Right Press worked" << std::endl;
		glfwGetCursorPos(window.glWindow, &_xPos, &_yPos);
		mouseCoords.x = _xPos;
		mouseCoords.y = _yPos;

		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << " : " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);
		_bombs.emplace_back(playerPosition, playerPosition, 5.0f, 1000);
	}

}



void mainGame::drawGame() {
	// Log log("mainGame", "drawGame", CRITICAL);

	while (!glfwWindowShouldClose(window.glWindow)) {

		_fpsLimiter.beginFrame();

		_time += 0.01;
		processInput();

		_camera.update();

		for (int i = 0; i < _bullets.size();) {
			if (_bullets[i].update() == true) {
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
				i++;
		}

		for (int i = 0; i < _bombs.size();) {
			if (_bombs[i].update() == true) {
				_bombs[i] = _bombs.back();
				_bombs.pop_back();
			}
			else
				i++;
		}

		//Set view port size and position every frame
		glfwGetFramebufferSize(window.glWindow, &_width, &_height);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		 _colourProgram.use();

		 glActiveTexture(GL_TEXTURE0);
		 GLint textureLocation = _colourProgram.getUniformLocation("mySampler");
		 glUniform1f(textureLocation, 0);

		// GLuint timeLocation = _colourProgram.getUniformLocation("time");
		// glUniform1f(timeLocation, _time);

		// set the camera matrix
		GLuint pLocation = _colourProgram.getUniformLocation("P");
		glm::mat4 cameraMatrix = _camera.getCameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		_spriteBatch.begin();

		glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static gameEngine::GLTexture texture = gameEngine::ResourceManager::getTexture("./textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
		gameEngine::Colour colour;
		colour.r = 255;
		colour.g = 255;
		colour.b = 255;
		colour.a = 255;

		_spriteBatch.draw(pos, uv, texture.id, 0.0f, colour);
		// _spriteBatch.draw(pos + glm::vec4(50, 0 ,0, 0), uv, texture.id, 0.0f, colour);

		for (int i = 0; i < _bullets.size(); i++) {
			_bullets[i].draw(_spriteBatch);
		}

		for (int i = 0; i < _bombs.size(); i++) {
			_bombs[i].draw(_spriteBatch);
		}

		_spriteBatch.end();
		_spriteBatch.renderBatch();

		glBindTexture(GL_TEXTURE_2D, 0);
		_colourProgram.unUse();

		window.swapBuffer();
		glfwPollEvents();

		_fps = _fpsLimiter.end();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 10) {
			// std::cout << "FPS: " << _fps << std::endl;
			frameCounter = 0;
		}
	}

	//properly destroy window and terminate glfw
	glfwDestroyWindow(window.glWindow);
	glfwTerminate();

	printf("goodbye gameEngine\n");
	_gameState = gameState::EXIT;
}

void mainGame::gameLoop(){
	// Log log("mainGame", "gameLoop", CRITICAL);
	while (_gameState != gameState::EXIT) {
		_camera.update();
		drawGame();
	}
}

void mainGame::cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	// std::cout << "X: " << xPos << "Y: " << yPos << std::endl;
}

void mainGame::cursorEnterCallback(GLFWwindow *window, int entered) {
	if (entered) {
		std::cout << "cursor in window" << std:: endl;
	}
	else {
		std::cout << "left window" << std::endl;

	}
}

void mainGame::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "Left button pressed" << std::endl;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		std::cout << "Left button released" << std::endl;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "Right button pressed" << std::endl;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		std::cout << "Right button pressed" << std::endl;
}
