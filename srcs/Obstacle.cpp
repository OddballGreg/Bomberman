#include "Obstacle.hpp" 

//Constructors
Obstacle::Obstacle()
{
	Log.log("Obstacle", "Constructor", CRITICAL);
}


Obstacle::Obstacle(const Obstacle &obj)
{
	Log.log("Obstacle", "Copy Constructor", CRITICAL);
}

Obstacle::~Obstacle()
{
	Log.log("Obstacle", "Deconstructor", CRITICAL);
}

Obstacle &Obstacle::operator =(const Obstacle &obj)
{ 
	Log.log("Obstacle", "= Operator", CRITICAL);
	return *this; 
}

// Setters

// Getters

// Methods
