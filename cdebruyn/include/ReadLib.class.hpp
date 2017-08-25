#ifndef READLIB_H
# define READLIB_H

# include <iostream>
# include <string>
# include <stdlib.h>
# include <vector>
# include <fstream>
# include <cstdio>
# include <array>
# include <algorithm>
# include <fcntl.h>
# include <stdio.h>
# include <memory>
# include <dlfcn.h>
# include <unistd.h>
# include "../shared/IDisplay.hpp"

# ifdef READ_LIB_FILE

bool				g_ai_flag = false;
int					g_height = 20;
int					g_width = 20;
int					g_verbosity = 0;
unsigned int		g_delay = 90000;
bool				userExit = false;
char				**g_av;

# else

extern bool			g_ai_flag;
extern int			g_height;
extern int			g_width;
extern int			g_verbosity;
extern unsigned int	g_delay;
extern bool			userExit;
extern char			**g_av;

# endif

class ReadLib {

	private:
		void*		_libHandle;
		std::string	_exect;

	protected:
		std::vector<std::string>				_libraries;
		std::vector<std::string>::size_type		_j;

	public:
		ReadLib( void );
		~ReadLib( void );
		ReadLib( ReadLib const & copy );
		
		const ReadLib&	operator=( ReadLib const & lib );	

		void			runlib( const int & i );
		std::string		execute( const char* cmd );
		void			openLib( const int & i );
		void			callRun( void );
		void			runGame(IDisplay *window) const;
};

#endif
