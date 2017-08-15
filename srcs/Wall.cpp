#include "Wall.hpp" 

//Constructors
Wall::Wall()
{
	Log.log("Wall", "Constructor", CRITICAL);
}

Wall::Wall(const Wall &obj)
{
	Log.log("Wall", "Copy Constructor", CRITICAL);
}

Wall::~Wall()
{
	Log.log("Wall", "Deconstructor", CRITICAL);
}

Wall &Wall::operator =(const Wall &obj)
{ 
	Log.log("Wall", "= Operator", CRITICAL);
	return *this; 
}

// Setters

// Getters

// Methods
