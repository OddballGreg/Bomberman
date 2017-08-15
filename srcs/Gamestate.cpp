#include "Gamestate.hpp" 

//Constructors
Gamestate::Gamestate(t_entityMap entities)
{
	Log.log("Gamestate", "Constructor", CRITICAL);
	this->_entities = entities;
}

Gamestate::Gamestate()
{
	IT WORKS
}

Gamestate::Gamestate(const Gamestate &obj)
{
	Log.log("Gamestate", "Copy Constructor", CRITICAL);
	this->_entities = obj._entities;
}

Gamestate::~Gamestate()
{
	Log.log("Gamestate", "Deconstructor", CRITICAL);
}

Gamestate &Gamestate::operator =(const Gamestate &obj)
{ 
	Log.log("Gamestate", "= Operator", CRITICAL);
	this->_entities = obj._entities;
	return *this; 
}

// Setters
void	Gamestate::setEntities(t_entityMap entities) { this->_entities = entities; }

// Getters
t_entityMap	Gamestate::getEntities() { return this->_entities; }

// Methods
