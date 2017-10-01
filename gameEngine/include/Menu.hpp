#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include "GameState.hpp"

enum class State {
    START,
    END,
    PAUSE,
    SETTINGS,
    SAVE,
    LOAD,
    LEVEL,
    START_SCREEN,
    PLAYING
};

class Menu {

public:
   
    Menu( void );
    Menu( State *state, GLFWwindow *window, int width, int height );
	~Menu( void );

	Menu( Menu const & copy );
    Menu& operator=( Menu const & copy );
    
    void    setWinPosition(nanogui::Window *window, Eigen::Vector2i vec);
    void    setWinLayout(nanogui::Window *window);

};

void        keyCallbackEvent(int key, int scancode, int action, int mods);
