#ifndef Vector_HPP
# define Vector_HPP

# include "../includes/Vector.hpp"

/*
	The Vector Class is a defintion of a point in 3D space with definition of it's velocity along these 3 axes.
*/

class Vector
{
	public:
		// Constructors & Destructors
		Vector(double x, double y, double z);
		Vector(double x, double y, double z, double dx, double dy, double dz);
		Vector(const Vector &obj);
		~Vector();

		// Operators Overloads
		Vector&		operator =(const Vector &obj);

		// Setters
		double		setX(); 
		double		setY(); 
		double		setZ(); 
		double		setDeltaX(); 
		double		setDeltaY(); 
		double		setDeltaZ(); 

		// Getters
		double		getX(); 
		double		getY(); 
		double		getZ(); 
		double		getDeltaX(); 
		double		getDeltaY(); 
		double		getDeltaZ(); 
		
		// Member Methods
		void		proceedVector(int times);
		void		reverseVector(int times);
		void		inverseVector();

	private:
		double 		_x;
		double 		_y;
		double 		_z;
		double 		_deltaX;
		double 		_deltaY;
		double 		_deltaZ;

};

#endif
