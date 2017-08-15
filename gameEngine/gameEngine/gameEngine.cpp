#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "Log.hpp"
#include "Logger.hpp"

#include "gameEngine.hpp"
#include <cstdlib>

int gameEngine::init() {
	// Log log("gameEngine", "init", CRITICAL);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	return 0;
}
