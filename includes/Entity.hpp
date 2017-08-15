#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "../includes/Log.hpp"
# include "../includes/Vector.hpp"


class Entity
{
	public:
		// Constructors & Destructors
		Entity(std::string name, std::string type, Vector location, Vector facing, bool destructable, std::string sprite, double collisionRadius, bool collideable);
		Entity(const Entity &obj);
		~Entity();

		// Operators Overloads
		Entity&		operator =(const Entity &obj);

		// Setters
		void	setName(std::string name);
		void	setType(std::string type);
		void	setLocation(Vector location);
		void	setFacing(Vector facing);
		void	setDestructable(bool destructable);
		void	setSprite(std::string sprite);
		void	setCollisionradius(double collisionRadius);
		void	setCollideable(bool collideable);

		// Getters
		std::string	getName();
		std::string	getType();
		Vector	getLocation();
		Vector	getFacing();
		bool	getDestructable();
		std::string	getSprite();
		double	getCollisionradius();
		bool	getCollideable();
		
		// Member Methods

	private:
		std::string	_name;
		std::string	_type;
		Vector	_location;
		Vector	_facing;
		bool	_destructable;
		std::string	_sprite;
		double	_collisionRadius;
		bool	_collideable;
};

#endif
