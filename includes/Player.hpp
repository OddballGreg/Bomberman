#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "../includes/Log.hpp"


class Player
{
	public:
		// Constructors & Destructors
		Player(std::string playerName, bool win, bool active);
		Player(const Player &obj);
		~Player();

		// Operators Overloads
		Player&		operator =(const Player &obj);

		// Setters
		void	setPlayername(std::string playerName);
		void	setWin(bool win);
		void	setActive(bool active);

		// Getters
		std::string	getPlayername();
		bool	getWin();
		bool	getActive();
		
		// Member Methods

	private:
		std::string	_playerName;
		bool	_win;
		bool	_active;
};

#endif
