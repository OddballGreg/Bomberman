#define READ_LIB_FILE
#include "./ReadLib.class.hpp"

typedef void	runFunction( void );

ReadLib::ReadLib( void ) {};

ReadLib::~ReadLib( void ) {};

ReadLib::ReadLib( ReadLib const & copy ) {
	*this = copy;
};
		
const ReadLib&	ReadLib::operator=( ReadLib const &lib ) {
	if (*this != lib)
		*this = lib;
	return lib;	
};

/**
 * This is where the libraries are loaded dynamically.
 */

void		ReadLib::openLib( const int & i ) {
	extern char **environ;

	logger.log_step_in("ReadLib| openlib() Called", CRITICAL);

	_libHandle = dlopen(_libraries.at("OpenGL.so", RTLD_LAZY | RTLD_LOCAL);
	
	if (_libHandle == NULL) {
		std::cout << "Falied loading library: OPenGL.so"<< std::endl; 
		std::cout << dlerror() << std::endl;
		return;
	} else {
		std::cout << "Cool beans... You library has loaded." << std::endl;
		callRun();
		dlclose(_libHandle);
	}
	execve(g_av[0], g_av, environ);
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
		display->initWindow(Coord(g_width, g_height));
		this->runGame(display);
	}
	catch (std::runtime_error(&e)) {
		try {
			display->exitWindow();
		}
		catch (...) {
		}
		std::cout << e.what() << std::endl;
	}

	if (!userExit) {
		sleep(2);
		system("reset");
	}

	destroy( display );

	logger.log_step_out("ReadLib| callRun() Completed", CRITICAL);
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

/*
** The gameplay logic
*/
void		ReadLib::runGame(IDisplay *window) const {
	logger.log_step_in("ReadLib| runGame() Called", CRITICAL);
	GameState		game;
	Direction		dir;
	struct timeval	now, reff;
	unsigned int	utime;

	logger.log("Readlib runGame() called", CRITICAL);
	game.setAIFlag(g_ai_flag);
	// window->setWindowSize(Coord(g_width, g_height));
	game.setSize(window->getWindowSize());
	game.resetSnake(Coord((window->getWindowSize().getX() / 2), window->getWindowSize().getY() / 2), Direction(WEST));
	gettimeofday(&reff, NULL);

	while (game.getMode() != MODE_END && !(window->getExit())) {

		game.setPaused(window->getPaused());

		game.runIteration();

		if (game.getMode() == MODE_PAUSE)
			window->drawPause();
		else
			window->drawScore(game.getScore());

		window->drawMap(game.getMap());

		if (game.getAIFlag() != true)
		{
			dir = window->getDirection();
			if (dir.getDirection() != LOST)
				game.setSnakeDir(dir.getDirection());
		}

		gettimeofday(&now, NULL);

		utime = static_cast<unsigned int>(abs(reff.tv_usec - now.tv_usec));

		if (utime < g_delay)
			usleep(g_delay - utime);

		gettimeofday(&reff, NULL);
	}
	userExit = window->getExit();

	window->drawGameOver(game.getScore());
	logger.log_step_out("ReadLib| runGame() Completed", CRITICAL);
}
