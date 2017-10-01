#include "../include/GameState.hpp"

GameState::GameState( void ) {};

GameState::~GameState( void ) {
};

GameState::GameState(GameState const &copy) {
	*this = copy;
};

GameState&		GameState::operator=(GameState const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};

void            GameState::setTitle(char *title) {
    this->TITLE = strdup(title);
};

void            GameState::startMenu(nanogui::FormHelper *gui, int width, int size) {
    this->TITLE = strdup("Welcome to Bomberman");

    printText2D(this->TITLE, 8, 80, 20);

    ref<Window> startWindow = gui->addWindow(Eigen::Vector2i(20, 20), this->TITLE);
    
    startWindow->setPosition(Vector2i(15, 15));
    startWindow->setLayout(new GroupLayout());

    /* No need to store a pointer, the data structure will be automatically
    freed when the parent window is deleted */
    new Label(startWindow, "Start a new Bomberman game", "sans-bold");
    Button *newBut = new Button(startWindow, "New Game");
    newBut->setCallback([] { std::cout << "pushed!" << std::endl; });
    newBut->setTooltip("Will initiate a new Bomberman game");

    new Label(startWindow, "Load an existing Bomberman game", "sans-bold");
    Button *loadBut = new Button(startWindow, "Load Game");
    loadBut->setCallback([] { std::cout << "pushed!" << std::endl; });
    loadBut->setTooltip("Will load an existing Bomberman game");

    new Label(startWindow, "Exit Bombeman", "sans-bold");
    Button *exitBut = new Button(startWindow, "Exit");
    exitBut->setCallback([] { std::cout << "pushed!" << std::endl; });
    exitBut->setTooltip("Are you sure?");
};

void            GameState::playMenu(int width, int size) {
    this->TITLE = strdup("Play Bomberman");

    printText2D(this->TITLE, 8, 80, 20);
};

void            GameState::endMenu(int width, int height) {
    this->TITLE = strdup("End Menu");
    
    char    text[256];
    sprintf(text, "%.2f sec", glfwGetTime());
    printText2D(text, 10, width, height);
};

void            GameState::pauseMenu(int width, int height) {
    this->TITLE = strdup("Pause Menu");
    
    char    text[256];
    sprintf(text, "%.2f sec", glfwGetTime());
    printText2D(text, 10, width, height);
};

void            GameState::settingsMenu(int width, int height) {
    this->TITLE = strdup("Settings Menu");
    
    char    text[256];
    sprintf(text, "%.2f sec", glfwGetTime());
    printText2D(text, 10, width, height);
};

void            GameState::saveMenu(int width, int height) {
    this->TITLE = strdup("Save Menu");
    
    char    text[256];
    sprintf(text, "%.2f sec", glfwGetTime());
    printText2D(text, 10, width, height);
};

void            GameState::loadMenu(int width, int height) {
    this->TITLE = strdup("Load Menu");
    
    char    text[256];
    sprintf(text, "%.2f sec", glfwGetTime());
    printText2D(text, 10, width, height);
};

void            GameState::levelMenu(int width, int height) {
    this->TITLE = strdup("Level Menu");
    
    char    text[256];
    sprintf(text, "%.2f sec", glfwGetTime());
    printText2D(text, 10, width, height);
};