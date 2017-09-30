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

void            GameState::startMenu(int width, int size) {
    this->TITLE = strdup("Welcome to Bomberman");

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