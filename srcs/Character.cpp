#include "Character.hpp" 

//Constructors
Character::Character(double lives, double max_lives, double speed, double attack_power, double bombs, double max_bombs)
{
	Log.log("Character", "Constructor", CRITICAL);
	this->_lives = lives;
	this->_max_lives = max_lives;
	this->_speed = speed;
	this->_attack_power = attack_power;
	this->_bombs = bombs;
	this->_max_bombs = max_bombs;
}


Character::Character(const Character &obj)
{
	Log.log("Character", "Copy Constructor", CRITICAL);
	this->_lives = obj._lives;
	this->_max_lives = obj._max_lives;
	this->_speed = obj._speed;
	this->_attack_power = obj._attack_power;
	this->_bombs = obj._bombs;
	this->_max_bombs = obj._max_bombs;
}

Character::~Character()
{
	Log.log("Character", "Deconstructor", CRITICAL);
}

Character &Character::operator =(const Character &obj)
{ 
	Log.log("Character", "= Operator", CRITICAL);
	this->_lives = obj._lives;
	this->_max_lives = obj._max_lives;
	this->_speed = obj._speed;
	this->_attack_power = obj._attack_power;
	this->_bombs = obj._bombs;
	this->_max_bombs = obj._max_bombs;
	return *this; 
}

// Setters
void	Character::setLives(double lives) { this->_lives = lives; }
void	Character::setMax_lives(double max_lives) { this->_max_lives = max_lives; }
void	Character::setSpeed(double speed) { this->_speed = speed; }
void	Character::setAttack_power(double attack_power) { this->_attack_power = attack_power; }
void	Character::setBombs(double bombs) { this->_bombs = bombs; }
void	Character::setMax_bombs(double max_bombs) { this->_max_bombs = max_bombs; }

// Getters
double	Character::getLives() { return this->_lives; }
double	Character::getMax_lives() { return this->_max_lives; }
double	Character::getSpeed() { return this->_speed; }
double	Character::getAttack_power() { return this->_attack_power; }
double	Character::getBombs() { return this->_bombs; }
double	Character::getMax_bombs() { return this->_max_bombs; }

// Methods
