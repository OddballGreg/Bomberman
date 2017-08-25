#define OPENGL_FILE
#include "../include/Window.class.hpp"

Window::Window( void ) {
	//
};

Window::~Window( void ) {
	//
};

Window::Window(Window const &copy) {
	*this = copy;
};

Window&		Window::operator=(Window const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};

int		Window::createWindow( void ) {
	GLFWwindow* window;

	/* Initialize the GLFW library */
	if (!glfwInit())
		return (-1);
	return (0);
};
