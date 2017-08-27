#define GLFW_FILE
#include "./GLFW.class.hpp"

GLFW::GLFW( void ) {

	//glfwSetErrorCallback(error_callback);

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

	glfwSetKeyCallback(_window, key_callback);

	/* Make the current window's context current */
	glfwMakeContextCurrent(_window);
	//gladLoadGLLoader((GLADloadproc), glfwGetProcAddress);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(_window)) {
		glfwGetFramebufferSize(_window, &WIDTH, &HEIGHT);
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	glfwDestroyWindow(_window);
};

const int		GLFW::exitWindow( void ) {
	//
};

void	GLFW::error_callback(int error, std::string descr)
{
    std::fprintf(stderr, "Error: %s\n", descr.c_str());
}

void 	GLFW::key_callback(GLFWwindow* window, int key, int scancode, \
		int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/*
** Linker Functions
*/
extern "C" GLFW*	createObject() {
	return new GLFW;
}

extern "C" void destroyObject( GLFW* object ) {
	delete object;
}
