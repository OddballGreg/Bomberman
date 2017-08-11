#include "Player.hpp"
#include "mainGame.h"
#include "gameEngine/ResourceManager.hpp"

#include <GLFW/glfw3.h>

Player::Player() {
    // _currentGunIndex = -1;
}
        
Player::~Player() {
    
}

void Player::pressKey(unsigned int keyID) {
    _keyPressed = keyID;
}

void Player::releaseKey(unsigned int keyID){
    _keyPressed = keyID;
}

void Player::init(int speed, glm::vec2 position, gameEngine::InputManager* inputManager, gameEngine::Camera2D* camera, std::vector<Bullet>* bullets) {
    _speed = speed;
    _position = position;
    _inputManager = inputManager;
    _camera = camera;
    _bullets = bullets;
    _keyPressed = 0;
    _colour.r = 255;
    _colour.g = 255;
    _colour.b = 255;
    _colour.a = 255;
}

void Player::addGun(Gun* gun) {
    
    _guns.push_back(gun);

    // if (_currentGunIndex == -1) {
    //     _currentGunIndex = 0;
    // }
}
        
void Player::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
    
    if (_keyPressed == GLFW_KEY_W) {
        std::cout << "W pressed" << std::endl;
        _position.y += _speed;
        _keyPressed = 0;
    }
    else if (_keyPressed == GLFW_KEY_S) {
        std::cout << "S pressed" << std::endl;
        _position.y -= _speed;
        _keyPressed = 0;
    }

    else if (_keyPressed == GLFW_KEY_A) {
        std::cout << "A pressed" << std::endl;
        _position.x -= _speed;
        _keyPressed = 0;
    }

    else if (_keyPressed == GLFW_KEY_D) {
        std::cout << "D pressed" << std::endl;
        _position.x += _speed;
        _keyPressed = 0;
    }

    // else if (_keyPressed == GLFW_KEY_1 && _guns.size() >= 0) {
    //     std::cout << "1 Pressed" << std::endl;
    //     _currentGunIndex = 0;
    //     _keyPressed = 0;
    // }

    // else if (_keyPressed == GLFW_KEY_2 && _guns.size() >= 1) {
    //     std::cout << "2 Pressed" << std::endl;
    //     _currentGunIndex = 1;
    //     _keyPressed = 0;
    // }

    // if (_currentGunIndex != -1) {
    //     // std::cout << "currentGunIndex = " << _currentGunIndex << std::endl;
    //     glm::vec2 mouseCoords = _inputManager->getMouseCoords();
    //     glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
        
    //     mouseCoords = _camera->convertScreenToWorld(mouseCoords);

    //     glm::vec2 direction;
    //     direction = glm::normalize(mouseCoords - centerPosition);
    //     _guns[_currentGunIndex]->update(_inputManager->isKeyDown(GLFW_MOUSE_BUTTON_RIGHT),
    //                                     centerPosition,
    //                                     direction,
    //                                     *_bullets);
    // }

    collideWithLevel(levelData);
}