#include "../include/Menu.hpp"

Menu::Menu() {

	nanogui::init();

    nanogui::mainloop();

	nanogui::shutdown();
};

Menu::~Menu() {};