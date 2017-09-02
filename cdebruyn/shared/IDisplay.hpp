#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <map>
# include <iostream>
# include <sstream>

# include <GLFW/glfw3.h>

class IDisplay {

public:
	virtual void		start( void ) = 0;
	virtual void		stop( void ) = 0;

	virtual const void	run( void ) = 0;
	virtual const void	render( void ) = 0;

    virtual int     getKey() = 0;
    virtual bool    createWindow(int, int) = 0;
    virtual void    refresh() = 0;
    virtual void    draw(int, int, char) = 0;
	virtual void    clearWindow() = 0;

};


typedef IDisplay*	createWindow_t();
typedef void		deleteWindow_t(IDisplay*);

#endif
