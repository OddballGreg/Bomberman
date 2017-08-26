#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <map>
# include <iostream>
# include <sstream>

class IDisplay {

public:
	virtual const int	initWindow( void ) = 0;
	virtual const int	exitWindow( void ) = 0;
};

extern "C" {
	IDisplay	*createWindow(void);
	void		deleteWindow(IDisplay *window);
}

#endif
