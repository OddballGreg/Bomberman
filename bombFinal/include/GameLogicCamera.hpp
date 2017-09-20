#pragma once

#include <memory>
#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Renderer.hpp"
//#include "../gameEngine/include/Sound.hpp"

#include "KeyInput.hpp"

using namespace gameEngine;

namespace Bomberman {

  class GameLogic {

  private:

    SceneObject player, enemy, tree, wall;
    
    //Sound bahSound;

    enum GameState {
      START_SCREEN,
      PLAYING
    };
    GameState gameState;

    enum EnemyState {
      FLYING_STRAIGHT,
      TURNING,
      DIVING_DOWN,
      DIVING_UP
    };
    EnemyState enemyState, enemyPreviousState;
    
    int       enemyFramesInCurrentState;
    float     enemyVerticalSpeed;

    double    startSeconds;
    int       seconds;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    bool      firstCam;

    void      initGame();

    void      processGame(const KeyInput &keyInput);

    void      processStartScreen(const KeyInput &keyInput);

    void      moveCamera(const KeyInput &keyInput);

    void      movePlayer(const KeyInput &keyInput);

    void      moveEnemy();

    float MAX_Z;
    float MIN_Z;
    
    float GROUND_Y;
    float FULL_ROTATION;
    
    float ENEMY_ROTATION_SPEED;
    float ENEMY_SPEED
    
    float PLAYER_ROTATION_SPEED;
    float PLAYER_SPEED;

  public:

    Renderer  *renderer;

    /**
     * Constructor
     */
    GameLogic();

    ~GameLogic() = default;

    void      process(const KeyInput &keyInput);
    void      render();
    float     lightModifier;
  };

}

