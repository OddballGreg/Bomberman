#include "Window.hpp"

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::Window::Window() {
	// Log log("Window", "Window", CRITICAL);
}

gameEngine::Window::~Window() {
	// Log log("Window", "~Window", CRITICAL);
}

int gameEngine::Window::create(int width, int height, std::string windowName){
	// Log log("Window", "create", CRITICAL);

	glWindow = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (!glWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(glWindow);

	glewExperimental = true;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK) {
		printf("glew init error\n");
	}

	if (!GLEW_VERSION_2_1) {
		printf("opengl 2.1 not supported\n");
		return false;
	}

	const GLubyte * p = glGetString(GL_VERSION);
	std::cout << "Graphics Driver: " << p << std::endl;

	const GLubyte * q = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "GLSL Version: " << q << std::endl;

	if (GLEW_ARB_vertex_array_object) {
		printf("genVertexArrays supported\n");
	}
	if (GLEW_APPLE_vertex_array_object) {
		printf("genVertexArrayAPPLE supported\n");
	}

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	std::printf("%u\n", vertexBuffer);
	GLuint vertexArrayID;

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void gameEngine::Window::swapBuffer() {
	// Log log("Window", "swapBuffer", CRITICAL);
	 glfwSwapBuffers(glWindow);
}

int gameEngine::Window::getScreenWidth(){
	// Log log("Window", "getScreenWidth", CRITICAL);
	return _width;
}

int gameEngine::Window::getScreenHeight(){
	// Log log("Window", "getScreenHeight", CRITICAL);
	return _height;
}
