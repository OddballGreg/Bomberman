#include "../include/MainComponent.class.hpp"
#include <iostream>
#include <cstring>

int		main(int argc, char **argv)
{
	if (argc == 1) {
		std::cout << argv[0] << std::endl;
		
		Window* win = new Window();
		win->createWindow();
	}
	return (0);
}
