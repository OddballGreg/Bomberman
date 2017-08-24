#ifndef MAIN_COMPONENT_H
# define MAIN_COMPONENT_H

# include <iostream>
# include <cstring>

class MainComponent {

protected:
	static const& int WIDTH{800};
	static const& int HEIGHT{600};
	static const& std::string TITLE{"Bomberman"};

public:

    MainComponent( void );
    ~MainComponent( void );

    MainComponent( MainComponent const & copy );
    MainComponent& operator=( MainComponent const & copy );

	void	start( void );
	void	stop( void );
	void	run( void );
	void	render( void );
	void	cleanUp( void );

	static void main( int argc, std::string argv );
};

#endif
