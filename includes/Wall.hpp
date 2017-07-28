#ifndef WALL_HPP
# define WALL_HPP

# include "Wall.hpp"

class Wall
{
	public:
		// Constructors & Destructors
		Wall(double radius);
		Wall(const Wall &obj);
		~Wall();

		// Operators Overloads
		Wall&		operator =(const Wall &obj);

		// Setters

		// Getters
		
		// Member Methods

	private:
};

#endif
