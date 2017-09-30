#include "../include/Menu.hpp"
#include "../include/GameState.hpp"
#include "../../include/KeyInput.hpp"

Bomberman::KeyInput *in = nullptr;

Menu::Menu( void ) {};

Menu::Menu( GLFWwindow *window, int width, int height ) {

    State state = State::START;

    switch(state) {
        case State::START : {
            GameState start;
            start.startMenu(width, height);
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

    glfwSetKeyCallback(window,
        [](GLFWwindow *, int key, int scancode, int action, int mods) {
            keyCallbackEvent(key, scancode, action, mods);
        }
    );

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

};

Menu::~Menu( void ) {
	glfwTerminate();
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

void keyCallbackEvent(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        in->esc = true;
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        in->space = true;
 
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        in->esc = false;
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        in->space = false;
    
}