#pragma once

#include <memory>
#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Renderer.hpp"
#include "../gameEngine/include/Menu.hpp"

#include "KeyInput.hpp"

using namespace gameEngine;

namespace Bomberman {
  class GameLogic {

  private:

    SceneObject enemy;
    SceneObject player;
    // SceneObject wall;
    //SceneObject bomber;


    enum GameState {
      START_SCREEN,
      PLAYING
    };

    GameState gameState;
	
	enum EnemyState {
    TURNING,
    WALKING_STRAIGHT
  };

	EnemyState enemyState;

    double startSeconds;
    int seconds;

    void initGame();
    void processGame(const KeyInput &keyInput);
    void processStartScreen(const KeyInput &keyInput);
    void moveEnemy();
    void movePlayer(const KeyInput &keyInput);

    float MAX_Z;
    float MIN_Z;
    float MAX_X;
    float MIN_X;
    
    float GROUND_Y;
    float FULL_ROTATION;
    
    float PLAYER_ROTATION_SPEED;
    float PLAYER_SPEED;
    
    float ENEMY_ROTATION_SPEED;
    float ENEMY_SPEED;
		
  public:

    Renderer *renderer;
    GameLogic();
    ~GameLogic();
    void process(const KeyInput &keyInput);

    void render();

    float lightModifier; 
  };

} 

