#include "../include/Menu.hpp"
#include "../include/GameState.hpp"
#include "../../include/KeyInput.hpp"

Bomberman::KeyInput *in = nullptr;

Menu::Menu( void ) {};

Menu::Menu( State *state, GLFWwindow *window, int width, int height ) {

    switch(*state) {
        case State::START_SCREEN : {
            GameState start;
            start.startMenu(width, height);
            break;
        }
        case State::PLAYING : {
            GameState playing;
            playing.playMenu(width, height);
            break;
        }
        case State::END : {
            GameState end;
            end.endMenu(width, height);
            break;
        }
        case State::PAUSE : {
            GameState pause;
            pause.pauseMenu(width, height);
            break;
        }
        case State::SETTINGS : {
            GameState settings;
            settings.settingsMenu(width, height);
            break;
        }
        case State::SAVE : {
            GameState save;
            save.saveMenu(width, height);
            break;
        }
        case State::LOAD : {
            GameState load;
            load.loadMenu(width, height);
            break;
        }
        case State::LEVEL : {
            GameState level;
            level.levelMenu(width, height);
            break;
        }
        default :
            break;
    }

};

Menu::~Menu( void ) {

};

Menu::Menu(Menu const &copy) {
	*this = copy;
};

Menu&		Menu::operator=(Menu const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};