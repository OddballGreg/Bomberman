#include "Zombie.hpp"
#include "Human.hpp"

Zombie::Zombie(){

}

Zombie::~Zombie() {
    
}

void Zombie::init(float speed, glm::vec2 pos) {
    _speed = speed;
    _position = pos;
    _health = 150.0f;

    _colour.r = 255;
    _colour.g = 0;
    _colour.b = 0;
    _colour.a = 255;
}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
    
    Human* closestHuman = getNearestHuman(humans);
    if (closestHuman != nullptr) {
        glm::vec2 direction = glm::normalize(closestHuman->getPosition() - _position);
        _position += direction * _speed;
    }

    collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
    Human* closestHuman = nullptr;
    float smallestDistance = 99999999.0f;

    for (int i = 0; i < humans.size(); i++) {
        glm::vec2 distVec = humans[i]->getPosition() - _position;
        float distance = glm::length(distVec);

        if (distance < smallestDistance) {
            smallestDistance = distance;
            closestHuman = humans[i];
        }
    }
    return closestHuman;
}