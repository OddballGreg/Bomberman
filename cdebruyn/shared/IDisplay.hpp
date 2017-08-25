#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <map>

# include <iostream>
# include <sstream>

# ifndef MAP
#  define MAP std::map<int, std::map<int, char> >
# endif

# ifndef MAP_EMPTY
#  define MAP_EMPTY		0
#  define MAP_OBSTICLE	1
#  define MAP_HEAD		2
#  define MAP_BODY		3
#  define MAP_FOOD		4
# endif

class IDisplay {

public:
	virtual	void		initWindow(void) = 0;
	virtual void		initWindow(Coord size) = 0;
	virtual void		exitWindow(void) = 0;
};

extern "C" {
	IDisplay	*createWindow(void);
	void		deleteWindow(IDisplay *window);
}

#endif
