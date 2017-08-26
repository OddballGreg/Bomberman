#define GLFW_FILE
#include "./GLFW.class.hpp"

GLFW::GLFW( void ) {

	/* Initialize the GLFW library */
	if (!glfwInit())
		exit(EXIT_FAILURE);
};

GLFW::~GLFW( void ) {
	glfwTerminate();
};

GLFW::GLFW(GLFW const &copy) {
	*this = copy;
};

GLFW&		GLFW::operator=(GLFW const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};

const int		GLFW::initWindow( void ) {
	GLFWwindow* _window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	_window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	wait(4);
	//glfwSetKeyCallback();

	glfwDestroyWindow(_window);
};

const int		GLFW::exitWindow( void ) {
	//
};

/*
** Linker Functions
*/
extern "C" GLFW*	createObject() {
	return new GLFW;
}

extern "C" void destroyObject( GLFW* object ) {
	delete object;
}
