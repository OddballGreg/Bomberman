#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "../includes/Log.hpp"
# include "../includes/Vector.hpp"
# include "../includes/Entity.hpp"


class Character
{
	public:
		// Constructors & Destructors
		Character(double lives, double max_lives, double speed, double attack_power, double bombs, double max_bombs);
		Character(const Character &obj);
		~Character();

		// Operators Overloads
		Character&		operator =(const Character &obj);

		// Setters
		void	setLives(double lives);
		void	setMax_lives(double max_lives);
		void	setSpeed(double speed);
		void	setAttack_power(double attack_power);
		void	setBombs(double bombs);
		void	setMax_bombs(double max_bombs);

		// Getters
		double	getLives();
		double	getMax_lives();
		double	getSpeed();
		double	getAttack_power();
		double	getBombs();
		double	getMax_bombs();
		
		// Member Methods

	private:
		double	_lives;
		double	_max_lives;
		double	_speed;
		double	_attack_power;
		double	_bombs;
		double	_max_bombs;
};

#endif
