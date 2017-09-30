#pragma once

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <unistd.h>

enum class	MenuState
{
    MAIN_MENU,
    SETTINGS,
    LOAD,
    EXIT
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
    void	loadMenu();

    void	menuHandler();
    void	renderMenu();
    void	popUpErrorMenu(std::string title, std::string message, std::string buttonText);

    bool	isTextFile(std::string);
};