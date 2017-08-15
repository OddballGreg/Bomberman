#include "Powerup.hpp" 

//Constructors
Powerup::Powerup(double value)
{
	Log.log("Powerup", "Constructor", CRITICAL);
	this->_value = value;
}


Powerup::Powerup(const Powerup &obj)
{
	Log.log("Powerup", "Copy Constructor", CRITICAL);
	this->_value = obj._value;
}

Powerup::~Powerup()
{
	Log.log("Powerup", "Deconstructor", CRITICAL);
}

Powerup &Powerup::operator =(const Powerup &obj)
{ 
	Log.log("Powerup", "= Operator", CRITICAL);
	this->_value = obj._value;
	return *this; 
}

// Setters
void	Powerup::setValue(double value) { this->_value = value; }

// Getters
double	Powerup::getValue() { return this->_value; }

// Methods
