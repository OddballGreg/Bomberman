#include "MainComponent.class.hpp"
#include <iostream>
#include <cstring>

int		main(int argc, std::string argv)
{
	if (argc == 1) {
		std::cout << argv[0] << std::endl;
		MainComponent mainComp;
		mainComp.main();
	}
	return (0);
}
