#ifndef GLFW_H
# define GLFW_H

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
# include "../shared/IDisplay.hpp"

class GLFW : public IDisplay {

protected:

public:

	GLFW( void );
	~GLFW( void );

	GLFW( GLFW const & copy );
	GLFW& operator=( GLFW const & copy );

	virtual const int		initWindow( void );
	virtual const int		exitWindow( void );
};

#endif
