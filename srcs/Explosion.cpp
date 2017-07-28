#include "Explosion.hpp" 

//Constructors
Explosion::Explosion(double duration)
{
	this->_duration = duration;
}

Explosion::Explosion(const Explosion &obj)
{
	this->_duration = obj.duration;
}

Explosion::~Explosion(){}

Explosion &Explosion::operator =(const Explosion &obj)
{ 
	this->_duration = obj.duration;
	return *this; 
}

// Setters
void	Explosion::setDuration(double duration) { this->_duration = duration; }

// Getters
double	Explosion::getDuration() { return this->_duration; }

// Methods
void	Explosion::tick()
{

}

