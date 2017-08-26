#ifndef __ENVIRON_H__
# define __ENVIRON_H__

# include "./GLFW/GLFW.class.hpp"

class Environ {

	public:
		Environ( void );

		extern "C" {
			GLFW*			createWindow( void );
			void			destroyWindow( GLFW* object );
		}
};

#endif