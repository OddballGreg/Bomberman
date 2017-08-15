#include "Player.hpp" 

//Constructors
Player::Player(std::string playerName, bool win, bool active)
{
	Log.log("Player", "Constructor", CRITICAL);
	this->_playerName = playerName;
	this->_win = win;
	this->_active = active;
}

Player::Player(const Player &obj)
{
	Log.log("Player", "Copy Constructor", CRITICAL);
	this->_playerName = obj._playerName;
	this->_win = obj._win;
	this->_active = obj._active;
}

Player::~Player()
{
	Log.log("Player", "Deconstructor", CRITICAL);
}

Player &Player::operator =(const Player &obj)
{ 
	Log.log("Player", "= Operator", CRITICAL);
	this->_playerName = obj._playerName;
	this->_win = obj._win;
	this->_active = obj._active;
	return *this; 
}

// Setters
void	Player::setPlayername(std::string playerName) { this->_playerName = playerName; }
void	Player::setWin(bool win) { this->_win = win; }
void	Player::setActive(bool active) { this->_active = active; }

// Getters
std::string	Player::getPlayername() { return this->_playerName; }
bool	Player::getWin() { return this->_win; }
bool	Player::getActive() { return this->_active; }

// Methods
