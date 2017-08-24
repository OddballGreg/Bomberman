#ifndef WINDOW_H
# define WINDOW_H

#if ((uname -s), Darwin) 
	# include <OpenGL/gl3.h>
#else
	# define GLFW_INCLUDE_ES2
	# include <GLES3/gl3.h>
#endif

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <iostream>
# include <cstring>

class Window {

protected:


public:

	Window( void );
	~Window( void );

	Window( Window const & copy );
	Window& operator=( Window const & copy );

	const void			createWindow( int width, int height, \
						std::string title );
	const void			render( void );
	const bool			isCloseRequested( void );

	const int			getWidth( void );
	const int			getHeight( void );
	const std::string	getTitle( void );
};

#endif
