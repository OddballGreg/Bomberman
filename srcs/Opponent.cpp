#include "Opponent.hpp" 

//Constructors
Opponent::Opponent()
{
	Log log("Opponent", "Constructor", CRITICAL);
}


Opponent::Opponent(const Opponent &obj)
{
	Log log("Opponent", "Copy Constructor", CRITICAL);
}

Opponent::~Opponent()
{
	Log log("Opponent", "Deconstructor", CRITICAL);
}

Opponent &Opponent::operator =(const Opponent &obj)
{ 
	Log log("Opponent", "= Operator", CRITICAL);
	return *this; 
}

// Setters

// Getters

// Methods
