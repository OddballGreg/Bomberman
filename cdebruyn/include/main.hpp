#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
# include <vector>
# include <fstream>
# include <fcntl.h>
# include <stdio.h>

extern "C" {
	#define _GNU_SOURCE
	#include <dlfcn.h>
}

// Graphic Library
#include "./GLFW.class.hpp"

// Library Reading Class
#include "./ReadLib.class.hpp"

#endif
