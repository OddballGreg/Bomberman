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

const void			createWindow( int width, int height, \
					std::string title ) {
	Display.setTitle(title);
	try {
		Display.setDisplayMode(new DisplayMode(width, height));
		Display.create();
	} catch ( ... ) {
		//
	}
};

const void			render( void ) {
	Display.update();
};

const bool			isCloseRequested( void ) {
	return Display.isCloseRequested();
};

const int			getWidth( void ) {
	return Display.getDisplayMode().getWidth();
};

const int			getHeight( void ) {
	return Display.getDisplayMode().getHeight();
};

const std::string	getTitle( void ) {
	return Display.getTitle();
};
