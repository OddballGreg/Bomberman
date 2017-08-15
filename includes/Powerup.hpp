#ifndef POWERUP_HPP
# define POWERUP_HPP

# include "../includes/Log.hpp"


class Powerup
{
	public:
		// Constructors & Destructors
		Powerup(double value);
		Powerup(const Powerup &obj);
		~Powerup();

		// Operators Overloads
		Powerup&		operator =(const Powerup &obj);

		// Setters
		void	setValue(double value);

		// Getters
		double	getValue();
		
		// Member Methods

	private:
		double	_value;
};

#endif
