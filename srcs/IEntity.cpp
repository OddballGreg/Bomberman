#include "../includes/IEntity.hpp" 

//Constructors
IEntity::IEntity(std::string name, Vector vector, bool destructable, std::string type, std::string sprite)
{
	this->_name = name;
	this->_vector = vector;
	this->_destructable = destructable;
	this->_type = type;
	this->_sprite = sprite;
}

IEntity::IEntity(const IEntity &obj)
{
	this->_name = obj.name;
	this->_vector = obj.vector;
	this->_destructable = obj.destructable;
	this->_type = obj.type;
	this->_sprite = obj.sprite;
}

IEntity::~IEntity(){}

IEntity &IEntity::operator =(const IEntity &obj)
{ 
	this->_name = obj.name;
	this->_vector = obj.vector;
	this->_destructable = obj.destructable;
	this->_type = obj.type;
	this->_sprite = obj.sprite;
	return *this; 
}

// Setters
void	IEntity::setName(std::string name) 			{ this->_name = name; }
void	IEntity::setVector(Vector vector) 			{ this->_vector = vector; }
void	IEntity::setDestructable(bool destructable) { this->_destructable = destructable; }
void	IEntity::setType(std::string type) 			{ this->_type = type; }
void	IEntity::setSprite(std::string sprite) 		{ this->_sprite = sprite; }

// Getters
std::string	IEntity::getName() 						{ return this->_name; }
Vector	IEntity::getVector() 						{ return this->_vector; }
bool	IEntity::getDestructable() 					{ return this->_destructable; }
std::string	IEntity::getType() 						{ return this->_type; }
std::string	IEntity::getSprite() 					{ return this->_sprite; }

// Methods
void	IEntity::move()
{

}

void	IEntity::die()
{

}

