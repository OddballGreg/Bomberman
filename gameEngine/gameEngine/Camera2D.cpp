#include "Camera2D.hpp"
#include <iostream>

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::Camera2D::Camera2D() : _width(500), _height(500), _needsMatrixUpdate(true), _scale(1.0f), _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f) {
    // Log log("Camera2D", "ARG Camera2D", CRITICAL);
}

gameEngine::Camera2D::~Camera2D() {
    // Log log("Camera2D", "Camera2D", CRITICAL);
}

void gameEngine::Camera2D::update() {
    // Log log("Camera2D", "update", CRITICAL);
    if (_needsMatrixUpdate) {

        // Camera translation / movement
        glm::vec3 translate(-_position.x + _width / 2, -_position.y + _height / 2, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);

        // Camera Scale / zoom
        glm::vec3 scale(_scale, _scale, 0.0f);
        _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
        
        _needsMatrixUpdate = false;
    }
}

void gameEngine::Camera2D::init(int width, int height) {
    // Log log("Camera2D", "init", CRITICAL);
    _width = width;
    _height = height;
     _orthoMatrix = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height);
}

void gameEngine::Camera2D::setPosition(const glm::vec2& newPosition){
    // Log log("Camera2D", "setPosition", CRITICAL);
    _position = newPosition;
    _needsMatrixUpdate = true;
}

glm::vec2 gameEngine::Camera2D::getPosition() {
    // Log log("Camera2D", "getPosition", CRITICAL);
    return _position;
}

void    gameEngine::Camera2D::setScale(float newScale) {
    // Log log("Camera2D", "setScale", CRITICAL);
    _scale = newScale;
    _needsMatrixUpdate = true;
}

float   gameEngine::Camera2D::getScale() {
    // Log log("Camera2D", "getScale", CRITICAL);
    return _scale;
}

glm::mat4 gameEngine::Camera2D::getCameraMatrix() {
    // Log log("Camera2D", "getCameraMatrix", CRITICAL);
    return _cameraMatrix;
}

glm::vec2 gameEngine::Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
        // Invert Y direction
        screenCoords.y = _height - screenCoords.y;
        // Make it so that 0 is the center
        screenCoords -= glm::vec2(_width / 2, _height / 2);
        // Scale the coordinates
        screenCoords /= _scale;
        // Translate with the camera position
        screenCoords += _position;
        return screenCoords;
    }