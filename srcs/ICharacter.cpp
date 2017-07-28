#include "../includes/ICharacter.hpp" 

//Constructors
ICharacter::ICharacter(double health, double speed, double attack_power, double bombs, double max_health, double max_bombs)
{
	this->_health = health;
	this->_speed = speed;
	this->_attack_power = attack_power;
	this->_bombs = bombs;
	this->_max_health = max_health;
	this->_max_bombs = max_bombs;
}

ICharacter::ICharacter(const ICharacter &obj)
{
	this->_health = obj.health;
	this->_speed = obj.speed;
	this->_attack_power = obj.attack_power;
	this->_bombs = obj.bombs;
	this->_max_health = obj.max_health;
	this->_max_bombs = obj.max_bombs;
}

ICharacter::~ICharacter(){}

ICharacter &ICharacter::operator =(const ICharacter &obj)
{ 
	this->_health = obj.health;
	this->_speed = obj.speed;
	this->_attack_power = obj.attack_power;
	this->_bombs = obj.bombs;
	this->_max_health = obj.max_health;
	this->_max_bombs = obj.max_bombs;
	return *this; 
}

// Setters
void	ICharacter::setHealth(double health)			{ this->_health = health; }
void	ICharacter::setSpeed(double speed)				{ this->_speed = speed; }
void	ICharacter::setAttack_power(double attack_power){ this->_attack_power = attack_power; }
void	ICharacter::setBombs(double bombs) 				{ this->_bombs = bombs; }
void	ICharacter::setMax_health(double max_health)	{ this->_max_health = max_health; }
void	ICharacter::setMax_bombs(double max_bombs)		{ this->_max_bombs = max_bombs; }

// Getters
double	ICharacter::getHealth()			{ return this->_health; }
double	ICharacter::getSpeed()			{ return this->_speed; }
double	ICharacter::getAttack_power() 	{ return this->_attack_power; }
double	ICharacter::getBombs() 			{ return this->_bombs; }
double	ICharacter::getMax_health() 	{ return this->_max_health; }
double	ICharacter::getMax_bombs() 		{ return this->_max_bombs; }

// Methods
void	ICharacter::move_north()
{

}

void	ICharacter::move_east()
{

}

void	ICharacter::move_south()
{

}

void	ICharacter::move_west()
{

}

void	ICharacter::heal(double amount)
{

}

void	ICharacter::increaseAP(double amount)
{

}

IEntity	ICharacter::placeBomb(Vector location)
{

}

