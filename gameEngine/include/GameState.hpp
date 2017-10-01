#pragma once

#include <iostream>
#include <cstring>
#include <nanogui/nanogui.h>

#include "text2D.hpp"
#include "Menu.hpp"

using namespace nanogui;

class GameState {

public:
    char   *TITLE = nullptr;

    GameState( void );
	~GameState( void );

	GameState( GameState const & copy );
	GameState& operator=( GameState const & copy );

    void    setTitle(char *title);
    void    startMenu(nanogui::FormHelper *gui, int width, int height);
    void    playMenu(int width, int size);
    void    endMenu(int width, int height);
    void    pauseMenu(int width, int height);
    void    settingsMenu(int width, int height);
    void    saveMenu(int width, int height);
    void    loadMenu(int width, int height);
    void    levelMenu(int width, int height);
};
