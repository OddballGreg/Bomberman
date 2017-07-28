#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include "../includes/ICharacter.hpp"

class ICharacter
{
	public:
		// Constructors & Destructors
		ICharacter(double health, double speed, double attack_power, double bombs, double max_health, double max_bombs);
		ICharacter(const ICharacter &obj);
		~ICharacter();

		// Operators Overloads
		ICharacter&		operator =(const ICharacter &obj);

		// Setters
		void	setHealth(double health);
		void	setSpeed(double speed);
		void	setAttack_power(double attack_power);
		void	setBombs(double bombs);
		void	setMax_health(double max_health);
		void	setMax_bombs(double max_bombs);

		// Getters
		double	getHealth();
		double	getSpeed();
		double	getAttack_power();
		double	getBombs();
		double	getMax_health();
		double	getMax_bombs();
		
		// Member Methods
		void	move_north();
		void	move_east();
		void	move_south();
		void	move_west();
		void	heal(double amount);
		void	increaseAP(double amount);
		IEntity	placeBomb(Vector location);

	private:
		double	_Health;
		double	_Speed;
		double	_Attack_power;
		double	_Bombs;
		double	_Max_health;
		double	_Max_bombs;
};

#endif
