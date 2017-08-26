#define MAIN_FILE
#include "../include/main.hpp"

int		main(int argc, char **argv)
{
	if (argc == 1) {
		std::cout << argv[0] << std::endl;
		
		ReadLib* lib = new ReadLib();
		lib->runlib(0);
		delete lib;
	}
	return (0);
}
