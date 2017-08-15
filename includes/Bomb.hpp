#ifndef BOMB_HPP
# define BOMB_HPP

# include "../includes/Log.hpp"
# include "../includes/Gamestate.hpp"


class Bomb
{
	public:
		// Constructors & Destructors
		Bomb(double secondstodetonation, double spread);
		Bomb(const Bomb &obj);
		~Bomb();

		// Operators Overloads
		Bomb&		operator =(const Bomb &obj);

		// Setters
		void	setSecondstodetonation(double secondstodetonation);
		void	setSpread(double spread);

		// Getters
		double	getSecondstodetonation();
		double	getSpread();
		
		// Member Methods
		void	tick();
		t_entityMap*	reverseVector(t_entityMap entities);

	private:
		double	_secondstodetonation;
		double	_spread;
};

#endif
