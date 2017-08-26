#define GLFW_FILE
#include "./GLFW.class.hpp"

GLFW::GLFW( void ) {
	//
};

GLFW::~GLFW( void ) {
	//
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
	GLFWwindow* window;

	/* Initialize the GLFW library */
	glfwInit();
	//if (glfwInit())
	//	return (-1);
	//return (0);
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
