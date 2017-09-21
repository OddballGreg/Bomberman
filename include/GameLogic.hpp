#pragma once

#include <memory>
#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Renderer.hpp"
#include "../gameEngine/include/Menu.hpp"
#include "../include/MapLoader.hpp"

#include <nanogui/nanogui.h>
#include "KeyInput.hpp"

using namespace gameEngine;

namespace Bomberman {
  class GameLogic {

  private:

    // SceneObject enemy;
    // SceneObject player;
    // SceneObject wall;
    //SceneObject bomber;
    MapLoader _maploader;
    SceneObject bomb;

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

    enum test_enum {
      Item1 = 0,
      Item2,
      Item3
    };
  
    bool bvar = true;
    double dvar = 3.1415926;
    int ivar = 12345678;
    float fvar = (float)dvar;
    std::string strval = "A string";
    test_enum enumval = Item2;
          
    bool  bombDropped;
    int   bombDelay;
		
  public:

    Screen *screen = nullptr;
    Renderer *renderer = nullptr;

    GameLogic();
    ~GameLogic();
    void process(const KeyInput &keyInput);

    void render();

    float lightModifier; 
  };

} 

