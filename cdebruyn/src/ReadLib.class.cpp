#define READ_LIB_FILE
# include "../include/ReadLib.class.hpp"

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

void			ReadLib::runlib( const int & i ) {

	std::ifstream	read;
	std::string		str;

	read.open("./lib/lib.txt");
	if (read.is_open()) {
		std::cout << "File ./lib/lib.txt is open." << std::endl;
		for (_j = 0; _j < 3 ; _j++) {
			getline(read, str);
			_libraries.push_back(str);
			std::cout << "Reading _libraries from ./lib: " << _libraries.at(_j)
			 << std::endl;
		}
		read.close();
	} else {
		std::cout << "\nError opening file ./lib/lib.txt" << std::endl;
	}

	this->openLib(i);

}
/**
 * This is where the libraries are loaded dynamically.
 */

void		ReadLib::openLib( const int & i ) {

	if (std::strncmp(OPENGL, "OpenGL.so", 9) == 0) {

		this->_libHandle = dlopen(OPENGL, RTLD_LAZY | RTLD_LOCAL);
	
		if (this->_libHandle == NULL) {
			std::cout << "Falied loading library: OpenGL" << std::endl; 
			std::cout << dlerror() << std::endl;
			return;
		} else {
			std::cout << "Cool beans... You library has loaded." << std::endl;
			callRun();
			dlclose(this->_libHandle);
		}
	} else {
		callRun();
	}
	return;
}

/**
 * This calls the `run` function in the indicated library
 */
void		ReadLib::callRun( void ) {

	IDisplay* (*create)();
	void	(*destroy)(IDisplay*);

	if (std::strncmp(OPENGL, "OpenGL.so", 9) == 0) {

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
			std::cout << "Initializing initWindow()" << std::endl;
			display->initWindow();
		}
		catch (std::runtime_error(&e)) {
			try {
				display->exitWindow();
			}
		 	catch (...) {
		 	}
			std::cout << e.what() << std::endl;
		}

		destroy( display );
	} else {
		//IDisplay* display;
	}
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
