#ifndef WINDOW_H
# define WINDOW_H

# include <iostream>
# include <cstring>

class Window {

protected:


public:

    MainComponent( void );
    ~MainComponent( void );

    MainComponent( MainComponent const & copy );
    MainComponent& operator=( MainComponent const & copy );

	const void			createWindow( int width, int height, \
						std::string title );
	const void			render( void );
	const bool			isCloseRequested( void );

	const int			getWidth( void );
	const int			getHeight( void );
	const std::string	getTitle( void );
};

#endif
