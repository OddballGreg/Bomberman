#ifndef __ENVIRON_H__
# define __ENVIRON_H__

# include "./GLFW/GLFW.class.hpp"

class Environ {

	public:
		Environ( void );

		extern "C" {
			GLFW*			createGLFW( void );
			void			destroyGLFW( GLFW* object );
		}
};

#endif
