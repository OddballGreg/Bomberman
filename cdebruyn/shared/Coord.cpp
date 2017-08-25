/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 09:33:40 by khansman          #+#    #+#             */
/*   Updated: 2017/06/16 09:33:42 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Coord.hpp"

/*
** Constructors and Destructors
*/
Coord::Coord(void): _x(0), _y(0) {
	//
}

Coord::Coord(int x, int y): _x(x), _y(y) {
	//
}

Coord::~Coord(void) {
	//
}

/*
** Copying
*/
Coord::Coord(const Coord &obj) {
	this->_x = obj._x;
	this->_y = obj._y;
}

Coord Coord::operator = (const Coord &obj) {
	this->_x = obj._x;
	this->_y = obj._y;

	return (*this);
}

/*
** Maths Operators
*/
Coord Coord::operator + (const Coord &obj) {
	this->_x += obj._x;
	this->_y += obj._y;

	return (*this);
}

Coord Coord::operator - (const Coord &obj) {
	this->_x -= obj._x;
	this->_y -= obj._y;

	return (*this);
}

Coord Coord::operator * (const Coord &obj) {
	this->_x *= obj._x;
	this->_y *= obj._y;

	return (*this);
}

Coord Coord::operator / (const Coord &obj) {
	this->_x /= obj._x;
	this->_y /= obj._y;

	return (*this);
}

/*
** Post and Pre Increment and Decrement
*/
Coord Coord::operator ++ (int) {
	Coord	tmp(*this);
	operator++();

	return (tmp);
}

Coord Coord::operator ++ (void) {
	this->_x += 1;
	this->_y += 1;

	return (*this);
}

Coord Coord::operator -- (int) {
	Coord	tmp(*this);
	operator--();

	return (tmp);
}

Coord Coord::operator -- (void) {
	this->_x -= 1;
	this->_y -= 1;

	return (*this);
}

/*
** Comparisons
*/
bool Coord::operator != (const Coord &obj) {
	return (this->_x != obj._x || this->_y != obj._y);
}

bool Coord::operator == (const Coord &obj) {
	return (this->_x == obj._x && this->_y == obj._y);
}

bool Coord::operator > (const Coord &obj) {
	return (this->_x > obj._x && this->_y > obj._y);
}

bool Coord::operator < (const Coord &obj) {
	return (this->_x < obj._x && this->_y < obj._y);
}

bool Coord::operator >= (const Coord &obj) {
	return (this->_x >= obj._x && this->_y >= obj._y);
}

bool Coord::operator <= (const Coord &obj) {
	return (this->_x <= obj._x && this->_y <= obj._y);
}

/*
** Getters
*/
int		Coord::getX(void) const {
	return (this->_x);
}

int		Coord::getY(void) const {
	return (this->_y);
}

/*
** Setters
*/
void	Coord::setX(int x) {
	this->_x = x;
}

void	Coord::setY(int y) {
	this->_y = y;
}

/*
** Basic Increment and Decrement
*/
void	Coord::incX(void) {
	this->_x++;
}

void	Coord::incY(void) {
	this->_y++;
}

void	Coord::decX(void) {
	this->_x--;
}

void	Coord::decY(void) {
	this->_y--;
}

/*
** Calculations
*/

unsigned int Coord::distTo(Coord &obj) const {
	unsigned int top = static_cast<unsigned int>( this->_x > obj.getX() ? this->_x - obj.getX() : obj.getX() - this->_x );
	unsigned int bottom = static_cast<unsigned int>( this->_y > obj.getY() ? this->_y - obj.getY() : obj.getY() - this->_y );

	return ( top + bottom );
}
Coord		Coord::mean(Coord c2) const {
	return (Coord((this->_x + c2._x) >> 1, (this->_y + c2._y) >> 1));
}

Direction	Coord::dirTo(Coord target) const {
	if (target == *this)
		return (Direction(LOST));
	else if (target.getX() == this->_x)
		return ((target.getY() > this->_y) ? Direction(NORTH) : Direction(SOUTH));
	else if (target.getY() == this->_y)
		return ((target.getX() > this->_x) ? Direction(EAST) : Direction(WEST));
	else if (target._y > this->_y && target._x > this->_x)
		return (Direction(NORTH_EAST));
	else if (target._y > this->_y && target._x < this->_x)
		return (Direction(NORTH_WEST));
	else if (target._y < this->_y && target._x > this->_x)
		return (Direction(SOUTH_EAST));
	else if (target._y < this->_y && target._x < this->_x)
		return (Direction(SOUTH_WEST));

	return (Direction(LOST));
}

/*
** Display
*/
std::ostream& operator << (std::ostream &o, const Coord &coord) {
	o << "( " << coord.getX() << "; " << coord.getY() << ")";

	return (o);
}
