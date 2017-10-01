//
// Created by Gabriel GROENER on 2017/09/25.
//
#pragma once

#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <utility>

class MenuScreen {

private:
	GLFWwindow  *_win;
//	MenuState   _menuState;
	nanogui::Screen* _screen;
	nanogui::Window *_mainMenu;

public:

	MenuScreen();
//	MenuScreen(int width, int height, const char& windowName);
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

//	void initializeMenu(int width, int height, const char* windowName);
	void initializeMenu(GLFWwindow * pWin);

};
