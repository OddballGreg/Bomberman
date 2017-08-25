/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Direction.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:13:03 by khansman          #+#    #+#             */
/*   Updated: 2017/06/16 14:13:05 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTION_HPP
# define DIRECTION_HPP

# include <iostream>

# include "Coord.hpp"

# define LOST   	0
# define NORTH 		1
# define EAST  		2
# define SOUTH 		3
# define WEST  		4
# define NORTH_EAST	5
# define NORTH_WEST	6
# define SOUTH_EAST	7
# define SOUTH_WEST	8

# define LEFT	   -1
# define RIGHT  	1
# define UP     	1
# define DOWN	   -1

class Coord;

class Direction {
public:
	Direction(void);
	Direction(char x, char y);
	Direction(char direction);
	~Direction(void);

	Direction(const Direction &obj);
	Direction operator = (const Direction &obj);

	char		getX(void) const;
	char		getY(void) const;
	char		getDirection(void) const;
	std::string getDirectionString(void) const;
	void		getTangent(Direction *dir1, Direction *dir2) const;
	void		getAdjacent(Direction *dir1, Direction *dir2) const;
	Direction	getComprised(Direction dir) const;

	void		setX(char x);
	void		setY(char y);
	void		setDirection(char direction);

	bool operator != (const Direction &obj);
	bool operator == (const Direction &obj);

	Coord		moveCoord(Coord coord) const;
	Direction	opposite(void) const;
	bool		similarTo(Direction dir1) const;

private:
	char	_x;
	char	_y;

};

std::ostream& operator << (std::ostream &o, const Direction &direction);

#endif
