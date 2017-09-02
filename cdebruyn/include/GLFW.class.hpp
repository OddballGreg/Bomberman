#ifndef GLFW_H
# define GLFW_H

//# include <GL/glew.h>
//# include <glad/glad.h>
# include <GLFW/glfw3.h>

# ifdef __APPLE__ 
#  include <OpenGL/gl3.h>
# else
#  define GLFW_INCLUDE_ES2
#  include <GLES3/gl3.h>
# endif

# include <iostream>
# include <cstring>
# include <cstdio>
# include "../shared/IDisplay.hpp"

class GLFW : public IDisplay {

protected:
	int WIDTH{800};
	int HEIGHT{600};
	const char* TITLE{"Bomberman"};

    GLFWwindow* _window;
    GLuint _vertex_buffer, _vertex_shader, _fragment_shader, _program;
    GLint _mvp_location, _vpos_location, _vcol_location;

public:

	GLFW( void );
	~GLFW( void );

	GLFW( GLFW const & copy );
	GLFW& operator=( GLFW const & copy );

	virtual const int		initWindow( void );
	virtual const int		exitWindow( void );

	static void		error_callback(int error, std::string descr);
	static void		key_callback(GLFWwindow* window, int key, int scancode, \
						int action, int mods);

};

# ifdef __APPLE__

extern "C" IDisplay*	createGLFW(void) {
	return new GLFW;
}

extern "C" void			deleteGLFW(IDisplay* window) {
	delete window;
}

# endif

#endif
