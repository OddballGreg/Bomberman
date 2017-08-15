#ifndef GAMESTATE_HPP
# define GAMESTATE_HPP

# include "../includes/Log.hpp"
# include "../includes/Entity.hpp"
# include <unordered_map>

typedef std::unordered_map<unsigned int, Entity> t_entityMap;

class Gamestate
{
	public:
		// Constructors & Destructors
		Gamestate(t_entityMap entities);
		Gamestate::Gamestate();
		Gamestate(const Gamestate &obj);
		~Gamestate();

		// Operators Overloads
		Gamestate&		operator =(const Gamestate &obj);

		// Setters
		void	setEntities(t_entityMap entities);

		// Getters
		t_entityMap	getEntities();
		
		// Member Methods

	private:
		t_entityMap	_entities;
};

#endif
