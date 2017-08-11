#include "Human.hpp"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human() {
    _frames = 0;
}

Human::~Human() {
    
}

void Human:: update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-1.0f, 1.0f);

    _position += _direction * _speed;

    if (_frames == 20) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
        _frames = 0;
    }
    else {
        _frames++;
    }

    if (collideWithLevel(levelData)) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
    }
    
}

void Human::init(float speed, glm::vec2 pos) {
    
    static std::mt19937 randomEngine(time(nullptr));
    
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _colour.r = 128;
    _colour.g = 128;
    _colour.b = 128;
    _colour.a = 255;
    _health = 20.0f;
    _speed = speed;
    _position = pos;
    _direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    if (_direction.length() == 0) {
        _direction = glm::vec2(1.0f, 0.0f);
    }
    _direction = glm::normalize(_direction);
}