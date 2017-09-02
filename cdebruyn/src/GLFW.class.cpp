#define GLFW_FILE
#include "../include/GLFW.class.hpp"

GLFW::GLFW( void ) {
	//glfwSetErrorCallback(error_callback);

	/* Initialize the GLFW library */
	if (!glfwInit())
		exit(EXIT_FAILURE);
};

GLFW::~GLFW( void ) {
	glfwDestroyWindow(_window);
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

const void		GLFW::run( void )
{
	isRunning = true;

    createWindow(HEIGHT, WIDTH);

	while (!glfwWindowShouldClose(_window))
		render();
};

const void		GLFW::render( void ) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);

        /* Poll for and process events */
        glfwPollEvents();
};

void	GLFW::error_callback(int error, std::string descr) {
    std::fprintf(stderr, "Error: %s\n", descr.c_str());
};

void 	GLFW::key_callback(GLFWwindow* window, int key, int scancode, \
		int action, int mods) {
    if (!(action == GLFW_PRESS))
        return;

    _key = key;
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_LEFT:
            break;
        case GLFW_KEY_RIGHT:
            break;
        case GLFW_KEY_DOWN:
            break;
        case GLFW_KEY_UP:
            break;
        case GLFW_KEY_SPACE:
            break;
        case GLFW_KEY_W:
            break;
        case GLFW_KEY_S:
            break;
        case GLFW_KEY_A:
            break;
        case GLFW_KEY_D:
            break;
    }
};

int     GLFW::getKey()
{
    return (this->_key);
};

bool    GLFW::createWindow(int height, int width)
{
    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(width, height, TITLE, NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
};

void    GLFW::refresh()
{

};

void    GLFW::draw(int, int, char)
{

};

void    GLFW::clearWindow()
{

};

void    GLFW::display( void )
{

};

void    GLFW::reshape(GLsizei width, GLsizei height)
{
};

void    GLFW::keyboard(unsigned char key, int x, int y)
{
    //glfwSetKeyCallback()
};

/*
** Linker Functions
*/
extern "C" GLFW*	createObject() {
	return new GLFW;
};

extern "C" void destroyObject( GLFW* object ) {
	delete object;
};
