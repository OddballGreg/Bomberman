#define MAIN_FILE
# include "../include/main.hpp"

int		main(int argc, char **argv)
{
	int	ret{0};

	if (argc == 1) {
		std::cout << argv[0] << std::endl;
		
		ReadLib* lib = new ReadLib();
		if ((ret = lib->openLib(0)) == -1) {
			GLFW* gl = new GLFW();
			gl->start();
		}
		delete lib;
	}
	return (0);
}

