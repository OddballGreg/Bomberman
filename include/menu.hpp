//
// Created by Gabriel GROENER on 2017/09/28.
//

#pragma once

#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <nanogui/screen.h>
#include <nanogui/widget.h>
#include <utility>

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

	public:

		MenuScreen(GLFWwindow * pWin);
		MenuScreen(MenuScreen const &);
		~MenuScreen();
		MenuScreen const & operator=(MenuScreen const &);

		void    mainMenu();
		void	settingsMenu();

		void	menuHandler();
		void	renderMenu();
};

