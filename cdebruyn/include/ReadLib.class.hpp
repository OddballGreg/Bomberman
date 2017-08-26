#ifndef READLIB_CLASS_H
# define READLIB_CLASS_H

# include <iostream>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include <fstream>
# include <cstdio>
# include <array>
# include <algorithm>
# include <fcntl.h>
# include <stdio.h>
# include <memory>

# ifdef __linux__
#  define _GNU_SOURCE
# endif
# include <dlfcn.h> 
# include <unistd.h>

# ifdef __APPLE__
#  define OPENGL "OpenGL.so"
# else
#  define OPENGL ""
# endif

# include "../shared/IDisplay.hpp"

# ifdef READ_LIB_FILE
char		**g_av;
# else
extern char	**g_av;
# endif

class ReadLib {

	private:
		void*	_libHandle;
		std::string	_exect;

	protected:
		std::vector<std::string>			_libraries;
		std::vector<std::string>::size_type	_j;

	public:
		ReadLib( void );
		~ReadLib( void );
		ReadLib( ReadLib const & copy );
		
		const ReadLib&	operator=( ReadLib const & lib );	

		void			runlib( const int & i );
		std::string		execute( const char* cmd );
		void			openLib( const int & i );
		void			callRun( void );
};

#endif
