#ifndef EXPLOSION_HPP
# define EXPLOSION_HPP

# include "../includes/Log.hpp"


class Explosion
{
	public:
		// Constructors & Destructors
		Explosion(double duration);
		Explosion(const Explosion &obj);
		~Explosion();

		// Operators Overloads
		Explosion&		operator =(const Explosion &obj);

		// Setters
		void	setDuration(double duration);

		// Getters
		double	getDuration();
		
		// Member Methods

	private:
		double	_duration;
};

#endif
