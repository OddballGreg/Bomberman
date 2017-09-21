
#include <memory>
#include <stdexcept>
#include <iostream>
#include "../include/GameLogic.hpp"


using namespace gameEngine;

namespace Bomberman {
  
  GameLogic::GameLogic() :
    enemy("enemy", "../resources/models/bomber/untitled", 20, "../resources/models/bomberBB/bomberBB.obj"),
    player("enemy", "../resources/models/bomber/untitled", 20, "../resources/models/bomberBB/bomberBB.obj"),
    bomb("bomb", "../resources/models/bomberman/bomb.obj", 1, "../resources/models/bomberman/cube.obj") {
    
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
    
    player.setFrameDelay(2);
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
    bombDelay = 200;

    // Initialise NanoGUI
    //Menu menu(renderer->getWindow());

    // player chase camera
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
    enemy.offset = glm::vec3(-1.2f, GROUND_Y, -4.0f);
    player.offset = glm::vec3(3.6f, GROUND_Y, 0.0f);
    player.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    bomb.offset = glm::vec3(0.0f,0.0f,0.0f);
    
    renderer->cameraPosition.x = player.offset.x;
    renderer->cameraPosition.y = 8;
    renderer->cameraPosition.z = (player.offset.z) + 4;
    
    player.startAnimating();
    enemy.startAnimating();
    bomb.startAnimating();
    
    startSeconds = glfwGetTime();
    
  }
  
  void GameLogic::moveEnemy() {
    enemyState = TURNING;
    
    float xDistance = player.offset.x - enemy.offset.x;
    float zDistance = player.offset.z - enemy.offset.z;
    float distance = sqrt(xDistance * xDistance + zDistance * zDistance);
    
    float enemyRelX = xDistance / distance;
    float enemyRelZ = zDistance / distance;
    
    float enemyDirectionX = -sin(enemy.rotation.y);
    float enemyDirectionZ = cos(enemy.rotation.y);
    
    float dotPosDir = enemyRelX * enemyDirectionX + enemyRelZ * enemyDirectionZ; // dot product
    
    if (dotPosDir > 0.98f) {
      enemyState = TURNING;
    } else
      enemyState = WALKING_STRAIGHT;
    
    if (enemyState == TURNING) {
      enemy.rotation.y -= ENEMY_ROTATION_SPEED;
      
    }
    
    if (enemy.offset.z > MAX_Z) {
      enemy.offset.z = MAX_Z;
      enemyState = TURNING;
    }
    if (enemy.offset.z < MIN_Z) {
      enemy.offset.z = MIN_Z;
      enemyState = TURNING;
    }
    if(enemy.offset.x > MAX_X) {
      enemy.offset.x = MAX_X;
      enemyState = TURNING;
    }
    if (enemy.offset.x < MIN_X) {
      enemy.offset.x = MIN_X;
      enemyState = TURNING;
    }
    
    enemy.offset.x += sin(enemy.rotation.y) * ENEMY_SPEED;
    enemy.offset.z -= cos(enemy.rotation.y) * ENEMY_SPEED;
    enemy.offset.y -= sin(enemy.rotation.x) * ENEMY_SPEED;
    
    enemy.animate();
    
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
    player.stopAnimating();
    
    if (keyInput.left) {
      player.rotation.y -= PLAYER_ROTATION_SPEED;
      // renderer->cameraRotation.y -= PLAYER_ROTATION_SPEED;
      // renderer->cameraPosition.x += sin(player.rotation.y) * 0.5f;
      // renderer->cameraPosition.z -= cos(player.rotation.y) * 0.5f;
      
      // while (player.collidesWith(tree.offset)) {
      //   player.rotation.y += PLAYER_ROTATION_SPEED;
      // }
      
      if (player.rotation.y < -FULL_ROTATION)
        player.rotation.y = 0.0f;
      player.startAnimating();
      
    } 
    else if (keyInput.right) {
      player.rotation.y += PLAYER_ROTATION_SPEED;
      // renderer->cameraRotation.y += PLAYER_ROTATION_SPEED;
      // while (player.collidesWith(tree.offset)) {
      //   player.rotation.y -= PLAYER_ROTATION_SPEED;
      // }
      
      
      if (player.rotation.y > FULL_ROTATION)
        player.rotation.y = 0.0f;
      player.startAnimating();
    }
    
    if (keyInput.up) {
      
      player.offset.x += sin(player.rotation.y) * PLAYER_SPEED;
      player.offset.z -= cos(player.rotation.y) * PLAYER_SPEED;
      // renderer->cameraPosition.x = (player.offset.x) + 4;
      // renderer->cameraPosition.z = (player.offset.z) + 4;
      std::cout << "x: " << player.offset.x << " z: " << player.offset.z << std::endl;
      
      // while (player.collidesWith(wall)) {
      //   player.offset.x -= sin(player.rotation.y) * PLAYER_SPEED;
      //   player.offset.z += cos(player.rotation.y) * PLAYER_SPEED;
      // }
      
      player.startAnimating();
      
    } else if (keyInput.down) {
      player.offset.x -= sin(player.rotation.y) * PLAYER_SPEED;
      player.offset.z += cos(player.rotation.y) * PLAYER_SPEED;
      // renderer->cameraPosition.z = (player.offset.z) + 4;
      
      // while (player.collidesWith(tree)) {
      //   player.offset.x += sin(player.rotation.y) * PLAYER_SPEED;
      //   player.offset.z -= cos(player.rotation.y) * PLAYER_SPEED;
      // }

      // player chase camera
    
      
      player.startAnimating();
    }
    
    // if (player.offset.z < MIN_Z + 1.0f)
    //   player.offset.z = MIN_Z + 1.0f;
    // if (player.offset.z > MAX_Z - 1.0f)
    //   player.offset.z = MAX_Z - 1.0f;
    
    // if (player.offset.x < player.offset.z)
    //   player.offset.x = player.offset.z;
    // if (player.offset.x > -(player.offset.z))
    //   player.offset.x = -(player.offset.z);

    if (player.offset.z > MAX_Z)
      player.offset.z = MAX_Z;
    if (player.offset.z < MIN_Z)
      player.offset.z = MIN_Z;
    if (player.offset.x > MAX_X)
      player.offset.x = MAX_X;
    if (player.offset.x < MIN_X)
      player.offset.x = MIN_X;


    if (keyInput.camRotXUp) {
      renderer->cameraRotation.x += cos(player.rotation.y) * 0.05f;
    } else if (keyInput.camRotXDown) {
      renderer->cameraRotation.x -= cos(player.rotation.y) * 0.05f;
    } else if (keyInput.camRotYUp) {
      renderer->cameraRotation.y += cos(player.rotation.y) * 0.05f;
    } else if (keyInput.camRotYDown) {
      renderer->cameraRotation.y -= cos(player.rotation.y) * 0.05f;
    } else if (keyInput.camRotZUp) {
      renderer->cameraRotation.z += cos(player.rotation.y) * 0.05f;
    } else if (keyInput.camRotZDown) {
      renderer->cameraRotation.z -= cos(player.rotation.y) * 0.05f;
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

    if (keyInput.space) {
      bombDropped = true;
      bomb.offset = player.offset;
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

    player.animate();
    
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
      

      // for (float i = 8; i < 14; i++) {
      //   wall.offset = glm::vec3(-i * 2, GROUND_Y + 1, -10.0f);
      //   renderer->render(wall, "wallTexture");
      // }
      renderer->render(enemy, "enemyTexture");
      renderer->render(player, "enemyTexture");
      
      if (bombDropped && bombDelay != 0) {
        renderer->render(bomb, "bombTexture");
        bombDelay--;
      }
      else if (bombDelay == 0) {
        bombDropped = false;
        bombDelay = 200;
      }
    }
    renderer->swapBuffers();
  }
  
}
