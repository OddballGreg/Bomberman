//
// Created by Gabriel GROENER on 2017/09/28.
//

#pragma once

#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <utility>

// remember to set visble to false for menus that you do not want to see.


enum class	MenuState
{
	MAIN_MENU,
	SETTINGS
};

class MenuScreen
{
	private:
		GLFWwindow  *_win;
		MenuState   _menuState;
		nanogui::Screen* _menuScreen;
		nanogui::Window *_mainMenu;

	public:

		MenuScreen(GLFWwindow * pWin);
		MenuScreen(MenuScreen const &);
		MenuScreen(MenuScreen &obj) = default;
		~MenuScreen();

		MenuScreen &operator = (MenuScreen &obj) = default;

		MenuScreen const & operator=(MenuScreen const &);

		void	mainMenu();
		void	settingsMenu();

		void	menuHandler();
		void	renderMenu();
};

