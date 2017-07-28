#include "Bomb.hpp" 

//Constructors
Bomb::Bomb(double SecondsToDetonation, double spread)
{
	this->_SecondsToDetonation = SecondsToDetonation;
	this->_spread = spread;
}

Bomb::Bomb(const Bomb &obj)
{
	this->_SecondsToDetonation = obj.SecondsToDetonation;
	this->_spread = obj.spread;
}

Bomb::~Bomb(){}

Bomb &Bomb::operator =(const Bomb &obj)
{ 
	this->_SecondsToDetonation = obj.SecondsToDetonation;
	this->_spread = obj.spread;
	return *this; 
}

// Setters
void	Bomb::setSecondstodetonation(double SecondsToDetonation) { this->_SecondsToDetonation = SecondsToDetonation; }
void	Bomb::setSpread(double spread) { this->_spread = spread; }

// Getters
double	Bomb::getSecondstodetonation() { return this->_SecondsToDetonation; }
double	Bomb::getSpread() { return this->_spread; }

// Methods
void	Bomb::tick()
{

}

t_entityMap	Bomb::*detonate(t_entityMap entities)
{

}

