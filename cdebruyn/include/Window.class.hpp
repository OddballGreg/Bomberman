#ifndef WINDOW_H
# define WINDOW_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# ifdef __APPLE__ 
#  include <OpenGL/gl3.h>
# else
#  define GLFW_INCLUDE_ES2
#  include <GLES3/gl3.h>
# endif


# include <iostream>
# include <cstring>

class Window {

protected:

public:

	Window( void );
	~Window( void );

	Window( Window const & copy );
	Window& operator=( Window const & copy );

	int		createWindow( void );
};

#endif
