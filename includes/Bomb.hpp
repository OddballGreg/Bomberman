#ifndef BOMB_HPP
# define BOMB_HPP

# include "Bomb.hpp"

class Bomb
{
	public:
		// Constructors & Destructors
		Bomb(double SecondsToDetonation, double spread);
		Bomb(const Bomb &obj);
		~Bomb();

		// Operators Overloads
		Bomb&		operator =(const Bomb &obj);

		// Setters
		void		setSecondstodetonation(double SecondsToDetonation);
		void		setSpread(double spread);

		// Getters
		double		getSecondstodetonation();
		double		getSpread();

		// Member Methods
		void		tick();
		t_entityMap	*detonate(t_entityMap entities);

	private:
		double		_Secondstodetonation;
		double		_Spread;
};

#endif
