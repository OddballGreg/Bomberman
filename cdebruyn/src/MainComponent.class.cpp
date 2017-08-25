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

MainComponent&	MainComponent::operator=( MainComponent const & copy ) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};
