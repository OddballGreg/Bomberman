#ifndef __ENVIRON_H__
# define __ENVIRON_H__

# include "../include/GLFW.class.hpp"

class Environ {

	public:
		Environ( void );

		extern "C" {
			GLFW*			createGLFW( void );
			void			destroyGLFW( GLFW* object );
		}
};

#endif
