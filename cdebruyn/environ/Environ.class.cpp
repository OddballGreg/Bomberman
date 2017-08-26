#include "../Environ.class.hpp"

Environ::Environ( void ) {};

GLFW*	Environ::createGLFW( void ) {
	return new GLFW;
};

void	Environ::destroyGLFW( GLFW* object ) {
	delete object;
};