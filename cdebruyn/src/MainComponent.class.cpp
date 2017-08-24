#include "../include/MainComponent.class.hpp"

MainComponent::MainComponent( void ) {
	//
};

MainComponent::~MainComponent( void ) {
	//
};

MainComponent::MainComponent( MainComponent const & copy ) {
	*this = copy;
};

MainComponent&	MainComponent& operator=( MainComponent const & copy ) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};

void	MainComponent::start( void ) {
	run();
};

void	MainComponent::stop( void ) {

};

void	MainComponent::run( void ) {
	while(!Window.isCloseRequested())
	{
		render();
	}
};

void	MainComponent::render( void ) {
	Window.render();
};

void	MainComponent::cleanUp( void ) {

};

static void MainComponent::main( int argc, std::string argv ) {
	Window.createWindow( WIDTH, HEIGHT, TITLE );

	// Create the environment for the game
	MainComponent game = new MainComponent();
	game.start();
};
