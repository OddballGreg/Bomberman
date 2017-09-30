//
// Created by Gabriel GROENER on 2017/09/28.
//

#include "../include/menu.hpp"


nanogui::Screen		*screen = nullptr;
bool bvar = true;
std::string strval = "A string";

MenuScreen::MenuScreen(GLFWwindow * pWin) : _win(pWin), _menuState(MenuState::MAIN_MENU)
{
    _menuScreen = new nanogui::Screen();
    _menuScreen->initialize(pWin, true);

    int width, height;
    glfwGetFramebufferSize(pWin, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(0);
    glfwSwapBuffers(pWin);

    nanogui::FormHelper *gui = new nanogui::FormHelper(_menuScreen);

    _mainMenu = gui->addWindow(nanogui::Vector2i({0, 0}), "Main Menu");
    _mainMenu->setLayout(new nanogui::GroupLayout());
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar)->setTooltip("Test tooltip.");
    gui->addVariable("string", strval);

    gui->addGroup("Other widgets");
    gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; })->setTooltip("Testing a much longer tooltip, that will wrap around to new lines multiple times.");;

    nanogui::Button *btn = new nanogui::Button(_mainMenu, "Hello, World!");
    btn->setTooltip("Hell");

    _mainMenu->setVisible(true);

//    _menuScreen->setVisible(true);

    _menuScreen->performLayout();
    _mainMenu->center();
}

MenuScreen::~MenuScreen()
{
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
}

void	MenuScreen::menuHandler()
{
    #if defined(NANOGUI_GLAD)
        #if defined(NANOGUI_SHARED) && !defined(GLAD_GLAPI_EXPORT)
                #define GLAD_GLAPI_EXPORT
            #endif

            #include <glad/glad.h>
    #else
        #if defined(__APPLE__)
            #define GLFW_INCLUDE_GLCOREARB
        #else
            #define GL_GLEXT_PROTOTYPES
        #endif
    #endif


//    screen = new nanogui::Screen; // uncomment everything
//    screen->initialize(_win, 1); //  comment the code below MenuScreen::mainMenu()

//     glfwSetCursorPosCallback(_win, [](GLFWwindow *, double x, double y)
//     	{
//     			screen->cursorPosCallbackEvent(x, y);
//     	}
//     );
//
//     glfwSetMouseButtonCallback(_win, [](GLFWwindow *, int button, int action, int modifiers)
//     	{
//     		screen->mouseButtonCallbackEvent(button, action, modifiers);
//     	}
//     );
//
//     glfwSetKeyCallback(_win, [](GLFWwindow *, int key, int scancode, int action, int mods)
//     	{
//     		screen->keyCallbackEvent(key, scancode, action, mods);
//     	}
//     );
//
//     glfwSetCharCallback(_win, [](GLFWwindow *, unsigned int codepoint)
//     	{
//     		screen->charCallbackEvent(codepoint);
//     	}
//     );

    //Break when going to game
    switch (_menuState)
    {
        case MenuState::MAIN_MENU :
            mainMenu();
            break;
        case MenuState::SETTINGS :
            settingsMenu();
            break;
    }
    _menuScreen->drawWidgets();
    _menuScreen->drawContents();

    //delete screen;
}

// remember to set visble to false for menus that you do not want to see it.

void	MenuScreen::mainMenu()
{

    /* NEEDED FOR EVERY NEW MENU */
    //screen = new nanogui::Screen; // move above
    //screen->initialize(_win, 1); // move above then uncomment above code

    //nanogui::FormHelper	*gui = new nanogui::FormHelper(screen);
    //nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Main MenuScreen");

    //nanoguiWindow->setLayout(new nanogui::GroupLayout);
    /* ************************* */

    //nanogui::Button	*new_game_button = new nanogui::Button(nanoguiWindow, "New Game");
    //new_game_button->setCallback([&]
                                /* {
                                     //ADD code for new game
                                     std::cout << "New Game SHOULD start now!!!\n";
                                 });*/

    /* NEEDED FOR EVERY NEW MENU */
    //screen->setVisible(1);
    //screen->performLayout();
    //nanoguiWindow->center();
    /* ************************* */

    /*while (!glfwWindowShouldClose(_win) && _menuState == MenuState::MAIN_MENU)
    {
        glfwPollEvents();
        renderMenu();
    }
    nanoguiWindow->dispose();
    delete new_game_button;
    delete gui;*/
    _mainMenu->setVisible(true);

}

void	MenuScreen::settingsMenu()
{

}

void	MenuScreen::renderMenu()
{
    int		width;
    int		height;

    //glfwGetFramebufferSize(_win, &width, &height);
    //glViewport( 0, 0, width, height);
    //glClear(GL_COLOR_BUFFER_BIT);
    _menuScreen->drawContents();
    _menuScreen->drawWidgets();
    //glfwSwapBuffers(_win);
}