#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <cstdio>
#include <array>
#include <algorithm>
#include <fcntl.h>
#include <stdio.h>
#include <memory>
#include <dlfcn.h>
#include <unistd.h>
#include "../shared/IDisplay.hpp"

class ReadLib {

	private:
		void*		_libHandle;
		std::string	_exect;
	public:
		ReadLib( void );
		~ReadLib( void );
		ReadLib( ReadLib const & copy );
		
		const ReadLib&	operator=( ReadLib const & lib );	

		void			runlib( const int & i );
		std::string		execute( const char* cmd );
		void			openLib( void );
		void			callRun( void );
		void			runGame(IDisplay *window) const;
};
