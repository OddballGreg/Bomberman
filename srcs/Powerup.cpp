#include "Powerup.hpp" 

//Constructors
Powerup::Powerup(double value)
{
	this->_value = value;
}

Powerup::Powerup(const Powerup &obj)
{
	this->_value = obj.value;
}

Powerup::~Powerup(){}

Powerup &Powerup::operator =(const Powerup &obj)
{ 
	this->_value = obj.value;
	return *this; 
}

// Setters
void	Powerup::setValue(double value) { this->_value = value; }

// Getters
double	Powerup::getValue() { return this->_value; }

// Methods
bool	Powerup::applyPowerup(IEntity target)
{

}

