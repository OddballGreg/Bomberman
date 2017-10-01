#include "../include/Menu.hpp"
#include "../include/GameState.hpp"
#include "../../include/KeyInput.hpp"

using namespace nanogui;

nanogui::Color colval(0.5f, 0.5f, 0.7f, 1.f);
nanogui::Screen *screen = nullptr;

Bomberman::KeyInput *in = nullptr;

Menu::Menu( void ) {};

Menu::Menu( State *state, GLFWwindow *window, int width, int height ) {

    screen = new nanogui::Screen();
    screen->initialize(window, true);

    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);

    switch(*state) {
        case State::START_SCREEN : {
            GameState start;
            start.startMenu(gui, width, height);
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

    screen->setVisible(true);
    screen->performLayout();
    // nanoguiWindow->center();

    glfwSetCursorPosCallback(window,
        [](GLFWwindow *, double x, double y) {
            screen->cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetMouseButtonCallback(window,
        [](GLFWwindow *, int button, int action, int modifiers) {
            screen->mouseButtonCallbackEvent(button, action, modifiers);
        }
    );

    glfwSetKeyCallback(window,
        [](GLFWwindow *, int key, int scancode, int action, int mods) {
            keyCallbackEvent(key, scancode, action, mods);
        }
    );

    glfwSetCharCallback(window,
        [](GLFWwindow *, unsigned int codepoint) {
            screen->charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *, int count, const char **filenames) {
            screen->dropCallbackEvent(count, filenames);
        }
    );

    glfwSetScrollCallback(window,
        [](GLFWwindow *, double x, double y) {
            screen->scrollCallbackEvent(x, y);
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *, int width, int height) {
            screen->resizeCallbackEvent(width, height);
        }
    );

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    
        glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    
        // Draw nanogui
        screen->drawContents();
        screen->drawWidgets();
    
        glfwSwapBuffers(window);
    }

};

Menu::~Menu( void ) {
    //glfwTerminate();
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

void        Menu::setWinPosition(nanogui::Window *window, Eigen::Vector2i vec) {
    window->setPosition(vec);
};

void        Menu::setWinLayout(nanogui::Window *window) {
    window->setLayout(new GroupLayout());
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