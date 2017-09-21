
#include <memory>
#include <stdexcept>
#include <iostream>
#include "../include/GameLogic.hpp"


using namespace gameEngine;

namespace Bomberman {
  
  GameLogic::GameLogic() : bomb("bomb", "../resources/models/bomberman/bomb.obj", 1, "../resources/models/bomberman/cube.obj")
  {
    _maploader.load_map("../maps/map.txt");
    
    renderer = &Renderer::getInstance("BombermanTestV1", 0, 0, 1.2f);
    
    Image startScreenTexture("../resources/images/bom.png");
    renderer->generateTexture("startScreen", startScreenTexture);
    
    Image groundTexture("../resources/images/floor.png");
    renderer->generateTexture("ground", groundTexture);
    
    Image skyTexture("../resources/images/sky.png");
    renderer->generateTexture("sky", skyTexture);

    Image bombTexture("../resources/images/floor.png");
    renderer->generateTexture("bomb", bombTexture);

    Image enemyTexture("../resources/images/floor.png");
    renderer->generateTexture("enemyTexture", enemyTexture);

    // Image treeTexture("../resources/models/Tree/tree.png");
    // renderer->generateTexture("treeTexture", treeTexture);
    
    _maploader._player[0].setFrameDelay(1);
    gameState = START_SCREEN;
    seconds = 0;
    lightModifier = -0.01f;
    enemyState = WALKING_STRAIGHT;
    MAX_Z = 10.0f;
    MIN_Z = -8.0f;
    MAX_X = 12.0f;
    MIN_X = -12.0f;
    
    GROUND_Y = -1.0f;
    FULL_ROTATION = 6.28f; // More or less 360 degrees in radians
    PLAYER_ROTATION_SPEED = 0.06f;
    PLAYER_SPEED = 0.08f;
    
    ENEMY_ROTATION_SPEED = 0.1f;
    ENEMY_SPEED = 0.05f;

    bombDropped = false;
    bombDelay = 100;

    // Initialise NanoGUI
    //Menu menu(renderer->getWindow());

    // player chase camera
    // renderer->cameraPosition = _maploader._player[0].offset;
    // renderer->cameraPosition.x = 0;
    // renderer->cameraPosition.y = 14;
    // renderer->cameraPosition.z = 0;
    //renderer->cameraPosition = player.offset;
    

    // Initialize camera angles
    // renderer->cameraRotation.x = 0.90f;
    // renderer->cameraRotation.y = 0.0f;
    // renderer->cameraRotation.z = 0.0f;

  }

  GameLogic::~GameLogic() {
      std::cout << "Camera Rotation x: " << renderer->cameraRotation.x << std::endl;
      std::cout << "Camera Rotation y: " << renderer->cameraRotation.y << std::endl;
      std::cout << "Camera Rotation z: " << renderer->cameraRotation.z << std::endl;
      std::cout << "Camera Position x: " << renderer->cameraPosition.x << std::endl;
      std::cout << "Camera Position y: " << renderer->cameraPosition.y << std::endl;
      std::cout << "Camera Position z: " << renderer->cameraPosition.z << std::endl;
  }
  
  void GameLogic::initGame() {
    _maploader._player[0].startAnimating();
    int i = _maploader._enemies.size();
    while (i > -1)
    {
      _maploader._enemies[i--].startAnimating();
    }
    
    renderer->cameraPosition.x = _maploader._player[0].offset.x;
    renderer->cameraPosition.y = 8;
    renderer->cameraPosition.z = (_maploader._player[0].offset.z) + 4;
    
    bomb.startAnimating();
    
    startSeconds = glfwGetTime();
    
  }
  
  void GameLogic::moveEnemy() {
    int i = _maploader._enemies.size();
    while (--i > -1)
    {
      enemyState = TURNING;
      
      float xDistance = _maploader._player[0].offset.x - _maploader._enemies[i].offset.x;
      float zDistance = _maploader._player[0].offset.z - _maploader._enemies[i].offset.z;
      float distance = sqrt(xDistance * xDistance + zDistance * zDistance);
      
      float enemyRelX = xDistance / distance;
      float enemyRelZ = zDistance / distance;
      
      float enemyDirectionX = -sin(_maploader._enemies[i].rotation.y);
      float enemyDirectionZ = cos(_maploader._enemies[i].rotation.y);
      
      float dotPosDir = enemyRelX * enemyDirectionX + enemyRelZ * enemyDirectionZ; // dot product
      
      if (dotPosDir > 0.98f) {
        enemyState = TURNING;
      } else
        enemyState = WALKING_STRAIGHT;
      
      if (enemyState == TURNING) {
        _maploader._enemies[i].rotation.y -= ENEMY_ROTATION_SPEED;
        
      }
      
      if (_maploader._enemies[i].offset.z > MAX_Z) {
        _maploader._enemies[i].offset.z = MAX_Z;
        enemyState = TURNING;
      }
      if (_maploader._enemies[i].offset.z < MIN_Z) {
        _maploader._enemies[i].offset.z = MIN_Z;
        enemyState = TURNING;
      }
      if(_maploader._enemies[i].offset.x > MAX_X) {
        _maploader._enemies[i].offset.x = MAX_X;
        enemyState = TURNING;
      }
      if (_maploader._enemies[i].offset.x < MIN_X) {
        _maploader._enemies[i].offset.x = MIN_X;
        enemyState = TURNING;
      }
      
      _maploader._enemies[i].offset.x += sin(_maploader._enemies[i].rotation.y) * ENEMY_SPEED;
      _maploader._enemies[i].offset.z -= cos(_maploader._enemies[i].rotation.y) * ENEMY_SPEED;
      _maploader._enemies[i].offset.y -= sin(_maploader._enemies[i].rotation.x) * ENEMY_SPEED;
    
      _maploader._enemies[i].animate();
    }
    
  }
  
  // void GameLogic::movePlayer(const KeyInput &keyInput) {
    
  //   if (keyInput.left) {
  //     player.rotation.y -= PLAYER_ROTATION_SPEED;
      
  //     if (player.rotation.y < -FULL_ROTATION)
  //       player.rotation.y = 0.0f;
      
      
  //   } else if (keyInput.right) {
  //       player.rotation.y += PLAYER_ROTATION_SPEED;
      
  //     if (player.rotation.y > FULL_ROTATION)
  //       player.rotation.y = 0.0f;
  //   }
    
  //   if (keyInput.down) {
      
  //     player.rotation.x -= PLAYER_TILT_SPEED;
      
  //     if (player.rotation.x < -0.75f)
  //       player.rotation.x = -0.75f;
      
      
  //   } else if (keyInput.up) {
      
  //     player.rotation.x += PLAYER_TILT_SPEED;
      
  //     if (player.rotation.x > 0.75f)
  //       player.rotation.x = 0.75f;
  //   }
    
  //   if (keyInput.space) {
  //     player.offset.x += sin(player.rotation.y) * PLAYER_SPEED;
  //     player.offset.z -= cos(player.rotation.y) * PLAYER_SPEED;
  //     player.offset.y -= sin(player.rotation.x) * PLAYER_SPEED;
  //   }
    
  //   if (player.offset.y < GROUND_Y + 0.5f)
  //     player.offset.y = GROUND_Y + 0.5f;
    
  //   if (player.offset.z > MAX_Z)
  //     player.offset.z = MAX_Z;
  //   if (player.offset.z < MIN_Z)
  //     player.offset.z = MIN_Z;
  //   if (player.offset.x > MAX_X)
  //     player.offset.x = MAX_X;
  //   if (player.offset.x < MIN_X)
  //     player.offset.x = MIN_X;
    
    
  //   // player chase camera
  //   renderer->cameraPosition = player.offset;
  //   renderer->cameraPosition.x -= sin(player.rotation.y) * 3.0f;
  //   renderer->cameraPosition.z += cos(player.rotation.y) * 3.0f;
  //   renderer->cameraPosition.y += sin(player.rotation.x) * 3.0f;
  //   renderer->cameraRotation = player.rotation;
  //   if (renderer->cameraPosition.y < GROUND_Y + 1.0f)
  //     renderer->cameraPosition.y = GROUND_Y + 1.0f;
    
  //   player.animate();
    
  //   if (enemy.collidesWith(player.offset)) {
  //     gameState = START_SCREEN;
  //     //add a sound here
  //     seconds = (glfwGetTime() - startSeconds);
  //   }
  // }

  void GameLogic::movePlayer(const KeyInput &keyInput) {
    _maploader._player[0].stopAnimating();
    
    if (keyInput.left) {
      _maploader._player[0].rotation.y -= PLAYER_ROTATION_SPEED;
      // renderer->cameraRotation.y -= PLAYER_ROTATION_SPEED;
      // renderer->cameraPosition.x += sin(player.rotation.y) * 0.5f;
      // renderer->cameraPosition.z -= cos(player.rotation.y) * 0.5f;
      
      // while (player.collidesWith(tree.offset)) {
      //   player.rotation.y += PLAYER_ROTATION_SPEED;
      // }
      
      if (_maploader._player[0].rotation.y < -FULL_ROTATION)
        _maploader._player[0].rotation.y = 0.0f;
      _maploader._player[0].startAnimating();
      
    } 
    else if (keyInput.right) {
      _maploader._player[0].rotation.y += PLAYER_ROTATION_SPEED;
      // renderer->cameraRotation.y += PLAYER_ROTATION_SPEED;
      // while (player.collidesWith(tree.offset)) {
      //   player.rotation.y -= PLAYER_ROTATION_SPEED;
      // }
      
      
      if (_maploader._player[0].rotation.y > FULL_ROTATION)
        _maploader._player[0].rotation.y = 0.0f;
      _maploader._player[0].startAnimating();
    }
    
    if (keyInput.up) {
      
      _maploader._player[0].offset.x += sin(_maploader._player[0].rotation.y) * PLAYER_SPEED;
      _maploader._player[0].offset.z -= cos(_maploader._player[0].rotation.y) * PLAYER_SPEED;
      // std::cout << "x: " << _maploader._player[0].offset.x << " z: " << _maploader._player[0].offset.z << std::endl;
      _maploader._player[0].offset.x += sin(_maploader._player[0].rotation.y) * PLAYER_SPEED;
      _maploader._player[0].offset.z -= cos(_maploader._player[0].rotation.y) * PLAYER_SPEED;
      // renderer->cameraPosition.x = (player.offset.x) + 4;
      // renderer->cameraPosition.z = (player.offset.z) + 4;
      
      // while (player.collidesWith(wall)) {
      //   player.offset.x -= sin(player.rotation.y) * PLAYER_SPEED;
      //   player.offset.z += cos(player.rotation.y) * PLAYER_SPEED;
      // }
      
      _maploader._player[0].startAnimating();
      
    } else if (keyInput.down) {
      _maploader._player[0].offset.x -= sin(_maploader._player[0].rotation.y) * PLAYER_SPEED;
      _maploader._player[0].offset.z += cos(_maploader._player[0].rotation.y) * PLAYER_SPEED;
      // renderer->cameraPosition.z = (player.offset.z) + 4;
      
      // while (player.collidesWith(tree)) {
      //   player.offset.x += sin(player.rotation.y) * PLAYER_SPEED;
      //   player.offset.z -= cos(player.rotation.y) * PLAYER_SPEED;
      // }

      // player chase camera
    
      
      _maploader._player[0].startAnimating();
    }
    
    // if (player.offset.z < MIN_Z + 1.0f)
    //   player.offset.z = MIN_Z + 1.0f;
    // if (player.offset.z > MAX_Z - 1.0f)
    //   player.offset.z = MAX_Z - 1.0f;
    
    // if (player.offset.x < player.offset.z)
    //   player.offset.x = player.offset.z;
    // if (player.offset.x > -(player.offset.z))
    //   player.offset.x = -(player.offset.z);

    if (_maploader._player[0].offset.z > MAX_Z)
      _maploader._player[0].offset.z = MAX_Z;
    if (_maploader._player[0].offset.z < MIN_Z)
      _maploader._player[0].offset.z = MIN_Z;
    if (_maploader._player[0].offset.x > MAX_X)
      _maploader._player[0].offset.x = MAX_X;
    if (_maploader._player[0].offset.x < MIN_X)
      _maploader._player[0].offset.x = MIN_X;


    if (keyInput.camRotXUp) {
      renderer->cameraRotation.x += cos(_maploader._player[0].rotation.y) * 0.05f;
    } else if (keyInput.camRotXDown) {
      renderer->cameraRotation.x -= cos(_maploader._player[0].rotation.y) * 0.05f;
    } else if (keyInput.camRotYUp) {
      renderer->cameraRotation.y += cos(_maploader._player[0].rotation.y) * 0.05f;
    } else if (keyInput.camRotYDown) {
      renderer->cameraRotation.y -= cos(_maploader._player[0].rotation.y) * 0.05f;
    } else if (keyInput.camRotZUp) {
      renderer->cameraRotation.z += cos(_maploader._player[0].rotation.y) * 0.05f;
    } else if (keyInput.camRotZDown) {
      renderer->cameraRotation.z -= cos(_maploader._player[0].rotation.y) * 0.05f;
    } else if (keyInput.camPosXUp) {
      renderer->cameraPosition.x += 0.5f;
    } else if (keyInput.camPosXDown) {
      renderer->cameraPosition.x -= 0.5f;
    } else if (keyInput.camPosYUp) {
      renderer->cameraPosition.y += 0.5f;
    } else if (keyInput.camPosYDown) {
      renderer->cameraPosition.y -= 0.5f;
    } else if (keyInput.camPosZUp) {
      renderer->cameraPosition.z += 0.5f;
    } else if (keyInput.camPosZDown) {
      renderer->cameraPosition.z -= 0.5f;
    }

    _maploader._player[0].animate();
    if (keyInput.space && !bombDropped) {
      bombDropped = true;
      bomb.offset = _maploader._player[0].offset;
      bomb.startAnimating();
    }

    // renderer->cameraPosition.x -= sin(player.rotation.y) * 3.0f;
    // renderer->cameraPosition.z += cos(player.rotation.y) * 3.0f;

    // renderer->cameraPosition = player.offset;
    // renderer->cameraPosition.x -= sin(player.rotation.y) * 5.0f;
    // renderer->cameraPosition.z += cos(player.rotation.y) * 5.0f;
    // renderer->cameraPosition.y = 16.0f;
    // renderer->cameraRotation = player.rotation;
    // renderer->cameraRotation.x = 1.1f;

    //renderer->cameraPosition = player.offset;
    renderer->cameraPosition.x = 0.0f;
    renderer->cameraPosition.z = 11.32f;
    renderer->cameraPosition.y = 16.0f;
    renderer->cameraRotation.x = 1.1f;

    
    // Uncomment to see the player's view of the world
    // renderer->cameraPosition = player.offset;
    // renderer->cameraPosition.y += 1.0f;
    // renderer->cameraRotation = player.rotation;
    
  }
  
  void GameLogic::processGame(const KeyInput &keyInput) {
    movePlayer(keyInput);
    moveEnemy();
  }
  
  void GameLogic::processStartScreen(const KeyInput &keyInput) {
    if (keyInput.enter) {
      initGame();
      gameState = PLAYING;
    }
  }
  
  void GameLogic::process(const KeyInput &keyInput) {
    switch (gameState) {
    case START_SCREEN:
      processStartScreen(keyInput);
      break;
    case PLAYING:
      processGame(keyInput);
      break;
    default:
      throw std::runtime_error("Urecognised game state");
    }
  }
  
  void GameLogic::render() {
    renderer->clearScreen();
    
    if (gameState == START_SCREEN) {
      
      renderer->renderRectangle("startScreen", glm::vec3(-1.0f, 1.0f, 1.0f),
			      glm::vec3(1.0f, -1.0f, 1.0f));
      
      if (seconds != 0) {
        renderer->write("Enemy avoided for " + intToStr(seconds) + " seconds",
			glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(-0.95f, -0.6f), glm::vec2(0.0f, -0.8f));
      }
      
    } else {
      
      renderer->renderRectangle("sky", glm::vec3(-1.0f, 1.0f, 1.0f),
			      glm::vec3(1.0f, -1.0f, 1.0f));
      
      // Draw the background
      
      renderer->renderRectangle("ground", glm::vec3(MIN_X, GROUND_Y, MIN_Z),
			      glm::vec3(MAX_X, GROUND_Y, MAX_Z), true);
      
      int i = _maploader._walls.size();
      while (--i > -1)
        renderer->render(_maploader._walls[i], "wallTexture");

      i = _maploader._obstacles.size();
      while (--i > -1)
        renderer->render(_maploader._obstacles[i], "wallTexture");

      i = _maploader._player.size();
      while (--i > -1)
        renderer->render(_maploader._player[i], "enemyTexture");

      i = _maploader._enemies.size();
      while (--i > -1)
        renderer->render(_maploader._enemies[i], "enemyTexture");

      if (bombDropped && bombDelay != 0) {
        renderer->render(bomb, "bombTexture");
        bombDelay--;
      }
      else if (bombDelay == 0) {
        bombDropped = false;
        bombDelay = 100;
        explosion.initialize("../SoundEngine/music/explosion.wav");
        explosion.play(false);
      }
    }
    renderer->swapBuffers();
  }
  
}
