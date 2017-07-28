#include "Obstacle.hpp" 

//Constructors
Obstacle::Obstacle(double radius)
{
	this->_radius = radius;
}

Obstacle::Obstacle(const Obstacle &obj)
{
	this->_radius = obj.radius;
}

Obstacle::~Obstacle(){}

Obstacle &Obstacle::operator =(const Obstacle &obj)
{ 
	this->_radius = obj.radius;
	return *this; 
}

// Setters
void	Obstacle::setRadius(double radius) { this->_radius = radius; }

// Getters
double	Obstacle::getRadius() { return this->_radius; }

// Methods
