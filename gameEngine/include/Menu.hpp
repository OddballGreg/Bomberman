#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include "GameState.hpp"

class Menu {

public:
    enum class State {
        START,
        END,
        PAUSE,
        SETTINGS,
        SAVE,
        LOAD,
        LEVEL
    };
    
    Menu( void );
    Menu( GLFWwindow *window, int width, int height );
	~Menu( void );

	Menu( Menu const & copy );
    Menu& operator=( Menu const & copy );
    
};

void        keyCallbackEvent(int key, int scancode, int action, int mods);
