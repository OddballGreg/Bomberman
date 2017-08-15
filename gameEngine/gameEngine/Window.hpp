#pragma once

#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

namespace gameEngine {
	enum WindowFlags {
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window {
		public:
			Window();
			~Window();

			int			create(int width, int height, std::string windowName);
			//int		create(std::string windowName, int width, int height, unsigned int currentFlags);
			void		swapBuffer();
			int		 	getScreenWidth();
			int		 	getScreenHeight();
			GLFWwindow * glWindow;
		private:
			// GLFWwindow	* _glWindow;
			//SDL_Window	* _sdlWindow;
			int			_width;
			int			_height;
	};
}