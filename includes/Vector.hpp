#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../includes/Log.hpp"


class Vector
{
	public:
		// Constructors & Destructors
		Vector(double x, double y, double z, double dx, double dy, double dz);
		Vector(const Vector &obj);
		~Vector();

		// Operators Overloads
		Vector&		operator =(const Vector &obj);

		// Setters
		void	setX(double x);
		void	setY(double y);
		void	setZ(double z);
		void	setDx(double dx);
		void	setDy(double dy);
		void	setDz(double dz);

		// Getters
		double	getX();
		double	getY();
		double	getZ();
		double	getDx();
		double	getDy();
		double	getDz();
		
		// Member Methods

	private:
		double	_x;
		double	_y;
		double	_z;
		double	_dx;
		double	_dy;
		double	_dz;
};

#endif
