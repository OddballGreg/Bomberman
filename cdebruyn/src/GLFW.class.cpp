#define GLFW_FILE
#include "../include/GLFW.class.hpp"

GLFW::GLFW( void ) {

//	glfwSetErrorCallback(error_callback);

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
/*	GLFWwindow* _window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	_window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, glfwGetPrimaryMonitor(), NULL);
	if (!_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(_window, key_callback);

	// Make the current window's context current
	glfwMakeContextCurrent(_window);
	// gladLoadGLLoader((GLADloadproc), glfwGetProcAddress);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(_window)) {
		glfwGetFrameBufferSize(_window, &WIDTH, &HEIGHT);
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	glfwDestroyWindow(_window);
*/
	GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
};

const int		GLFW::exitWindow( void ) {
	//
};

void	GLFW::error_callback(int error, std::string descr)
{
    std::fprintf(stderr, "Error: %s\n", descr);
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
