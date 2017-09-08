#ifndef MENU_HPP
# define MENU_HPP

#include <glm/glm.hpp>

# include "../gameEngine/gameEngine/gameEngine.hpp"
# include "../gameEngine/gameEngine/SpriteBatch.hpp"
# include "Logger.hpp"
# include "Log.hpp"

enum menuCode {
	menuCodeExit,
	menuCodeRestart,
	menuCodeContinue
};

class Menu
{
	public:
		// Constructors & Destructors
		Menu();
		Menu(const Menu &obj);
		~Menu();

		// Operators Overloads
		Menu&		operator =(const Menu &obj);

		// Setters

		// Getters
		
		// Member Methods
		void	drawMenu(SpriteBatch &spriteBatch);
		menuCode	show(SpriteBatch &spriteBatch, gameEngine::Window window);
		bool	clickedExit(double x, double y);
		bool	clickedRestart(double x, double y);
		bool	clickedContinue(double x, double y);

	private:
};

#endif