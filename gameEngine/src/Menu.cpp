#include "../include/Menu.hpp"

Menu::Menu(Screen *screen) {

    Color colval(0.5f, 0.5f, 0.7f, 1.f);

    bool enabled = true;
    FormHelper *gui = new FormHelper(screen);
    ref<Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar);
    gui->addVariable("string", strval);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar)->setSpinnable(true);
    gui->addVariable("float", fvar);
    gui->addVariable("double", dvar)->setSpinnable(true);

    gui->addGroup("Complex types");
    gui->addVariable("Enumeration", enumval, enabled)
       ->setItems({"Item 1", "Item 2", "Item 3"});
    gui->addVariable("Color", colval);

    gui->addGroup("Other widgets");
    gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; });

    screen->setVisible(true);
    screen->performLayout();
    window->center();

};

Menu::~Menu() {};