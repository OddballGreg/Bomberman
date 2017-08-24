#include "Window.class.hpp"

Window::Window( void ) {
	//
};

Window::~Window( void ) {
	//
};

Window::Window(Window const &copy) {
	*this = copy;
}

Window&		Window::operator=(Window const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
}

const void			Window::createWindow( int width, int height, \
					std::string title ) {
	Display.setTitle(title);
	try {
		Display.setDisplayMode(new DisplayMode(width, height));
		Display.create();
	} catch ( ... ) {
		//
	}
};

const void			Window::render( void ) {
	Display.update();
};

const bool			Window::isCloseRequested( void ) {
	return Display.isCloseRequested();
};

const int			Window::getWidth( void ) {
	return Display.getDisplayMode().getWidth();
};

const int			Window::getHeight( void ) {
	return Display.getDisplayMode().getHeight();
};

const std::string	Window::getTitle( void ) {
	return Display.getTitle();
};
