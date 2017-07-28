#ifndef OBSTACLE_HPP
# define OBSTACLE_HPP

# include "Obstacle.hpp"

class Obstacle
{
	public:
		// Constructors & Destructors
		Obstacle(double radius);
		Obstacle(const Obstacle &obj);
		~Obstacle();

		// Operators Overloads
		Obstacle&		operator =(const Obstacle &obj);

		// Setters
		void	setRadius(double radius);

		// Getters
		double	getRadius();
		
		// Member Methods

	private:
		double	_Radius;
};

#endif
