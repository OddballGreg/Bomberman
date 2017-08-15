#include "Entity.hpp" 

//Constructors
Entity::Entity(std::string name, std::string type, Vector location, Vector facing, bool destructable, std::string sprite, double collisionRadius, bool collideable)
{
	Log.log("Entity", "Constructor", CRITICAL);
	this->_name = name;
	this->_type = type;
	this->_location = location;
	this->_facing = facing;
	this->_destructable = destructable;
	this->_sprite = sprite;
	this->_collisionRadius = collisionRadius;
	this->_collideable = collideable;
}


Entity::Entity(const Entity &obj)
{
	Log.log("Entity", "Copy Constructor", CRITICAL);
	this->_name = obj._name;
	this->_type = obj._type;
	this->_location = obj._location;
	this->_facing = obj._facing;
	this->_destructable = obj._destructable;
	this->_sprite = obj._sprite;
	this->_collisionRadius = obj._collisionRadius;
	this->_collideable = obj._collideable;
}

Entity::~Entity()
{
	Log.log("Entity", "Deconstructor", CRITICAL);
}

Entity &Entity::operator =(const Entity &obj)
{ 
	Log.log("Entity", "= Operator", CRITICAL);
	this->_name = obj._name;
	this->_type = obj._type;
	this->_location = obj._location;
	this->_facing = obj._facing;
	this->_destructable = obj._destructable;
	this->_sprite = obj._sprite;
	this->_collisionRadius = obj._collisionRadius;
	this->_collideable = obj._collideable;
	return *this; 
}

// Setters
void	Entity::setName(std::string name) { this->_name = name; }
void	Entity::setType(std::string type) { this->_type = type; }
void	Entity::setLocation(Vector location) { this->_location = location; }
void	Entity::setFacing(Vector facing) { this->_facing = facing; }
void	Entity::setDestructable(bool destructable) { this->_destructable = destructable; }
void	Entity::setSprite(std::string sprite) { this->_sprite = sprite; }
void	Entity::setCollisionradius(double collisionRadius) { this->_collisionRadius = collisionRadius; }
void	Entity::setCollideable(bool collideable) { this->_collideable = collideable; }

// Getters
std::string	Entity::getName() { return this->_name; }
std::string	Entity::getType() { return this->_type; }
Vector	Entity::getLocation() { return this->_location; }
Vector	Entity::getFacing() { return this->_facing; }
bool	Entity::getDestructable() { return this->_destructable; }
std::string	Entity::getSprite() { return this->_sprite; }
double	Entity::getCollisionradius() { return this->_collisionRadius; }
bool	Entity::getCollideable() { return this->_collideable; }

// Methods
