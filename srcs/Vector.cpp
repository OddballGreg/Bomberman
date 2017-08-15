#include "Vector.hpp" 

//Constructors
Vector::Vector(double x, double y, double z, double dx, double dy, double dz)
{
	Log.log("Vector", "Constructor", CRITICAL);
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_dx = dx;
	this->_dy = dy;
	this->_dz = dz;
}

Vector::Vector(const Vector &obj)
{
	Log.log("Vector", "Copy Constructor", CRITICAL);
	this->_x = obj._x;
	this->_y = obj._y;
	this->_z = obj._z;
	this->_dx = obj._dx;
	this->_dy = obj._dy;
	this->_dz = obj._dz;
}

Vector::~Vector()
{
	Log.log("Vector", "Deconstructor", CRITICAL);
}

Vector &Vector::operator =(const Vector &obj)
{ 
	Log.log("Vector", "= Operator", CRITICAL);
	this->_x = obj._x;
	this->_y = obj._y;
	this->_z = obj._z;
	this->_dx = obj._dx;
	this->_dy = obj._dy;
	this->_dz = obj._dz;
	return *this; 
}

// Setters
void	Vector::setX(double x) { this->_x = x; }
void	Vector::setY(double y) { this->_y = y; }
void	Vector::setZ(double z) { this->_z = z; }
void	Vector::setDx(double dx) { this->_dx = dx; }
void	Vector::setDy(double dy) { this->_dy = dy; }
void	Vector::setDz(double dz) { this->_dz = dz; }

// Getters
double	Vector::getX() { return this->_x; }
double	Vector::getY() { return this->_y; }
double	Vector::getZ() { return this->_z; }
double	Vector::getDx() { return this->_dx; }
double	Vector::getDy() { return this->_dy; }
double	Vector::getDz() { return this->_dz; }

// Methods
