#include "Explosion.hpp" 

//Constructors
Explosion::Explosion(double duration)
{
	Log log("Explosion", "Constructor", CRITICAL);
	this->_duration = duration;
}


Explosion::Explosion(const Explosion &obj)
{
	Log log("Explosion", "Copy Constructor", CRITICAL);
	this->_duration = obj._duration;
}

Explosion::~Explosion()
{
	Log log("Explosion", "Deconstructor", CRITICAL);
}

Explosion &Explosion::operator =(const Explosion &obj)
{ 
	Log log("Explosion", "= Operator", CRITICAL);
	this->_duration = obj._duration;
	return *this; 
}

// Setters
void	Explosion::setDuration(double duration) { this->_duration = duration; }

// Getters
double	Explosion::getDuration() { return this->_duration; }

// Methods
