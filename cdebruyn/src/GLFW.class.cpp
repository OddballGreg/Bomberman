#define GLFW_FILE
#include "../include/GLFW.class.hpp"

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

void	GLFW::start( void ) {
	if (isRunning)
		return;

	this->run();
};

void	GLFW::stop( void ) {
	if (!isRunning)
		return;
	
	isRunning = false;
};

const void		GLFW::run( void ) {
    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

	while (!glfwWindowShouldClose(_window)) {
		render();
	}
};

const void		GLFW::render( void ) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);

        /* Poll for and process events */
        glfwPollEvents();
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
