#include "../includes/Player.hpp" 

//Constructors
Player::Player(std::string playerName, bool win, bool active)
{
	this->_playerName = playerName;
	this->_win = win;
	this->_active = active;
}

Player::Player(const Player &obj)
{
	this->_playerName = obj.playerName;
	this->_win = obj.win;
	this->_active = obj.active;
}

Player::~Player(){}

Player &Player::operator =(const Player &obj)
{ 
	this->_playerName = obj.playerName;
	this->_win = obj.win;
	this->_active = obj.active;
	return *this; 
}

// Setters
void		Player::setPlayername(std::string playerName) { this->_playerName = playerName; }
void		Player::setWin(bool win) { this->_win = win; }
void		Player::setActive(bool active) { this->_active = active; }

// Getters
std::string	Player::getPlayername() { return this->_playerName; }
bool		Player::getWin() { return this->_win; }
bool		Player::getActive() { return this->_active; }

// Methods
