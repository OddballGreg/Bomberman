//
// Created by Gabriel GROENER on 2017/09/28.
//

#include "../include/menu.hpp"


nanogui::Screen		*screen = nullptr;

MenuScreen::MenuScreen(GLFWwindow * pWin) : _win(pWin), _menuState(MenuState::MAIN_MENU)
{

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

    // glfwSetCursorPosCallback(_win, [](GLFWwindow *, double x, double y)
    // 	{
    // 			screen->cursorPosCallbackEvent(x, y);
    // 	}
    // );

    // glfwSetMouseButtonCallback(_win, [](GLFWwindow *, int button, int action, int modifiers)
    // 	{
    // 		screen->mouseButtonCallbackEvent(button, action, modifiers);
    // 	}
    // );

    // glfwSetKeyCallback(_win, [](GLFWwindow *, int key, int scancode, int action, int mods)
    // 	{
    // 		screen->keyCallbackEvent(key, scancode, action, mods);
    // 	}
    // );

    // glfwSetCharCallback(_win, [](GLFWwindow *, unsigned int codepoint)
    // 	{
    // 		screen->charCallbackEvent(codepoint);
    // 	}
    // );

    //Break when going to game
    while (1)
    {
        switch (_menuState)
        {
            case MenuState::MAIN_MENU :
                mainMenu();
                break;
            case MenuState::SETTINGS :
                settingsMenu();
                break;
        }
    }

    //delete screen;
}

void	MenuScreen::mainMenu()
{
    /* NEEDED FOR EVERY NEW MENU */
    screen = new nanogui::Screen; // move above
    screen->initialize(_win, 1); // move above then uncomment above code

    nanogui::FormHelper	*gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Main MenuScreen");

    nanoguiWindow->setLayout(new nanogui::GroupLayout);
    /* ************************* */

    nanogui::Button	*new_game_button = new nanogui::Button(nanoguiWindow, "New Game");
    new_game_button->setCallback([&]
                                 {
                                     //ADD code for new game
                                     std::cout << "New Game SHOULD start now!!!\n";
                                 });

    /* NEEDED FOR EVERY NEW MENU */
    screen->setVisible(1);
    screen->performLayout();
    nanoguiWindow->center();
    /* ************************* */

    while (!glfwWindowShouldClose(_win) && _menuState == MenuState::MAIN_MENU)
    {
        glfwPollEvents();
        renderMenu();
    }
    nanoguiWindow->dispose();
    delete new_game_button;
    delete gui;
}

void	MenuScreen::settingsMenu()
{

}

void	MenuScreen::renderMenu()
{
    int		width;
    int		height;

    glfwGetFramebufferSize(_win, &width, &height);
    glViewport( 0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    screen->drawContents();
    screen->drawWidgets();
    glfwSwapBuffers(_win);
}