#define READ_LIB_FILE
#include "../include/ReadLib.class.hpp"

typedef void	runFunction( void );

ReadLib::ReadLib( void ) {};

ReadLib::~ReadLib( void ) {};

ReadLib::ReadLib( ReadLib const & copy ) {
	*this = copy;
};
		
const ReadLib&	ReadLib::operator=( ReadLib const &lib ) {
	//if (*this != lib)
	//	*this = lib;
	return lib;	
};

/**
 * This is where the libraries are loaded dynamically.
 */

void		ReadLib::openLib( void ) {
	extern char **environ;

	_libHandle = dlopen("OpenGL.so", RTLD_LAZY | RTLD_LOCAL);
	
	if (_libHandle == NULL) {
		std::cout << "Falied loading library: OpenGL.so"<< std::endl; 
		std::cout << dlerror() << std::endl;
		return;
	} else {
		std::cout << "Cool beans... You library has loaded." << std::endl;
		callRun();
		dlclose(_libHandle);
	}
}

/**
 * This calls the `run` function in the indicated library
 */
void		ReadLib::callRun( void ) {

	IDisplay* (*create)();
	void	(*destroy)(IDisplay*);

	// reset errors
	dlerror();
	create = (IDisplay* (*)())dlsym(_libHandle, "createObject");
	destroy = (void (*)(IDisplay*))dlsym(_libHandle, "destroyObject");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Trouble finding `run`: " << dlerror() << std::endl;
		dlclose(_libHandle);
	}

	IDisplay* display = (IDisplay*)create();
	try {
		//
	}
	catch (std::runtime_error(&e)) {
		try {
			//
		}
		catch (...) {
		}
		std::cout << e.what() << std::endl;
	}

	destroy( display );
};

/**
 * The bash script is executed to load the library.
 */
std::string		ReadLib::execute( const char* cmd ) {
    std::array<char, 512> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
};
