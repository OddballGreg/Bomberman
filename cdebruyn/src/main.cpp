#include "../include/ReadLib.class.hpp"
#include <iostream>
#include <cstring>

int		main(int argc, char **argv)
{
	if (argc == 1) {
		std::cout << argv[0] << std::endl;
		
		ReadLib* lib = new ReadLib();
		lib->openLib();
	}
	return (0);
}
