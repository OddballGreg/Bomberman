#include "Bomb.hpp" 

//Constructors
Bomb::Bomb(double secondstodetonation, double spread)
{
	Log.log("Bomb", "Constructor", CRITICAL);
	this->_secondstodetonation = secondstodetonation;
	this->_spread = spread;
}


Bomb::Bomb(const Bomb &obj)
{
	Log.log("Bomb", "Copy Constructor", CRITICAL);
	this->_secondstodetonation = obj._secondstodetonation;
	this->_spread = obj._spread;
}

Bomb::~Bomb()
{
	Log.log("Bomb", "Deconstructor", CRITICAL);
}

Bomb &Bomb::operator =(const Bomb &obj)
{ 
	Log.log("Bomb", "= Operator", CRITICAL);
	this->_secondstodetonation = obj._secondstodetonation;
	this->_spread = obj._spread;
	return *this; 
}

// Setters
void	Bomb::setSecondstodetonation(double secondstodetonation) { this->_secondstodetonation = secondstodetonation; }
void	Bomb::setSpread(double spread) { this->_spread = spread; }

// Getters
double	Bomb::getSecondstodetonation() { return this->_secondstodetonation; }
double	Bomb::getSpread() { return this->_spread; }

// Methods
void	Bomb::tick()
{
}

t_entityMap	Bomb::*reverseVector(t_entityMap entities)
{
}

