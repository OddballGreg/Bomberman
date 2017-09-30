#pragma once

#include <iostream>
#include <cstring>

#include "text2D.hpp"
#include "Menu.hpp"

class GameState {

public:
    char   *TITLE = nullptr;

    GameState( void );
	~GameState( void );

	GameState( GameState const & copy );
	GameState& operator=( GameState const & copy );

    void    setTitle(char *title);
    void    startMenu(int width, int height);
    void    endMenu(int width, int height);
    void    pauseMenu(int width, int height);
    void    settingsMenu(int width, int height);
    void    saveMenu(int width, int height);
    void    loadMenu(int width, int height);
    void    levelMenu(int width, int height);
};
