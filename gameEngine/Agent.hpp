#pragma once

#include <glm/glm.hpp>
#include "gameEngine/SpriteBatch.hpp"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;


class Zombie;
class Human;

class Agent {
    public:
        Agent();
        virtual ~Agent();

        void                draw(gameEngine::SpriteBatch& _spriteBatch);

        virtual void        update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;

        bool                collideWithLevel(const std::vector<std::string>& levelData);
        bool                collideWithAgent(Agent* agent);
        bool                applyDamage(float damage);
        
        glm::vec2           getPosition() const;
    
    protected:

        void                checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePosition, float x, float y);
        
        void                collideWithTile(glm::vec2 tilePos);
        float               _health;
        glm::vec2           _position;
        float               _speed;
        gameEngine::Colour  _colour;
        unsigned int        _keyPressed;

};