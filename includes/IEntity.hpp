#ifndef IENTITY_HPP
# define IENTITY_HPP

# include "../includes/IEntity.hpp"

class IEntity
{
	public:
		// Constructors & Destructors
		IEntity(std::string name, Vector vector, bool destructable, std::string type, std::string sprite, double collisionRadius, bool collideable);
		IEntity(const IEntity &obj);
		~IEntity();

		// Operators Overloads
		IEntity&	operator =(const IEntity &obj);

		// Setters
		void		setName(std::string name);
		void		setVector(Vector vector);
		void		setDestructable(bool destructable);
		void		setType(std::string type);
		void		setSprite(std::string sprite);
		void		setCollisionRadius(double collisionRadius);
		void		setCollideable(bool collideable);

		// Getters
		std::string	getName();
		Vector		getVector();
		bool		getDestructable();
		std::string	getType();
		std::string	getSprite();
		double		getCollisionRadius();
		bool		getCollideable();

		// Member Methods
		void		move();
		void		die();

	private:
		std::string	_Name;
		Vector		_Vector;
		bool		_Destructable;
		std::string	_Type;
		std::string	_Sprite;
		double		_collisionRadius
		bool		_collideable
		// Variable for facing
};

#endif
