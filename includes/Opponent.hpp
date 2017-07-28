#ifndef OPPONENT_HPP
# define OPPONENT_HPP

# include "Opponent.hpp"

class Opponent
{
	public:
		// Constructors & Destructors
		Opponent();
		Opponent(const Opponent &obj);
		~Opponent();

		// Operators Overloads
		Opponent&		operator =(const Opponent &obj);

		// Setters

		// Getters
		
		// Member Methods
		void	runAI(t_entityMap entities);

	private:
};

#endif
