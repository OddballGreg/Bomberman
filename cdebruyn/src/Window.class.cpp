#include "../include/Window.class.hpp"

Window::Window( void ) {
	//
};

Window::~Window( void ) {
	//
};

Window::Window(Window const &copy) {
	*this = copy;
}

Window&		Window::operator=(Window const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
}

const void			Window::createWindow( int width, int height, \
					std::string title ) {

	glfwSetErrorCallback(errorCallback);
	
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	this.window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!this.window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(this.window, isClosedRequested);
	glfwMakeContextCurrent(this.window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);	
	glfwSwapInterval(1);

	glewExperimental = true;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK) {
		std::cerr << "glew init error\n" << std::endl;
	}

	if (!GLEW_VERSION_2_1) {
		std::cerr << "opengl 2.1 not supported\n" << std::endl;
		return false;
	}

	const GLubyte * p = glGetString(GL_VERSION);
	std::cout << "Graphics Driver: " << p << std::endl;

	const GLubyte * q = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "GLSL Version: " << q << std::endl;

	if (GLEW_ARB_vertex_array_object) {
		std::cout << "genVertexArrays supported" << std::endl;
	}
	if (GLEW_APPLE_vertex_array_object) {
		std::cout << "genVertexArrayAPPLE supported" << std::endl;
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

};

const void			Window::render( void ) {
	Display.update();
};

const void			Window::isCloseRequested( GLFWwindow* window, int key, \
					int scancode, int mods ) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
};

const int			Window::getWidth( void ) {
	return Display.getDisplayMode().getWidth();
};

const int			Window::getHeight( void ) {
	return Display.getDisplayMode().getHeight();
};

const std::string	Window::getTitle( void ) {
	return Display.getTitle();
};

void				Window::errorCallback(int error, std::string description) {
	std::fprintf(stderr, "Error: %s\n", descr); 
};
