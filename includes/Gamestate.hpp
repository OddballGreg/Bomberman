#ifndef GAMESTATE_HPP
# define GAMESTATE_HPP

# include "../includes/Gamestate.hpp"

typedef std::unordered_map<IEntity> t_entityMap;

class Gamestate
{
	public:
		// Constructors & Destructors
		Gamestate();
		Gamestate(const Gamestate &obj);
		~Gamestate();

		// Operators Overloads
		Gamestate&		operator =(const Gamestate &obj);

		// Setters

		// Getters
		t_entityMap		getEntities();

		// Member Methods
		void			spawnPlayer(Vector pos);
		void			spawnOpponent(Vector pos);
		void			spawnObstacle(Vector pos);
		void			spawnBomb(Vector pos);

	private:
		t_entityMap 	_entities;

};

#endif
