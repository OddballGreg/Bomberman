#include "../includes/Gamestate.hpp" 

//Constructors
Gamestate::Gamestate(std::string text, int value)
Gamestate::Gamestate(<args>)
{
	this->_text = text
	this->_value = value
}

Gamestate::Gamestate(const Gamestate &obj)
{
	this->_text = obj.text
	this->_value = obj.value
}

Gamestate::~Gamestate(){}

Gamestate &Gamestate::operator =(const Gamestate &obj)
{ 
	this->_text = obj.text
	this->_value = obj.value
	return *this; 
}

// Setters

// Methods
