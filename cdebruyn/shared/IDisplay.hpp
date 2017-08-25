#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <map>
# include <iostream>
# include <sstream>

class IDisplay {

public:

};

extern "C" {
	IDisplay	*createWindow(void);
	void		deleteWindow(IDisplay *window);
}

#endif
