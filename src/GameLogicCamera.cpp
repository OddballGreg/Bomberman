
#include <memory>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "../include/GameLogic.hpp"


using namespace gameEngine;

namespace Bomberman {
  
  GameLogic::GameLogic() :
    player("player", "../resources/models/bomber/untitled",
	 20, "../resources/models/bomberBB/bomberBB.obj"),
    enemy("enemy", "../resources/models/enemy/bomberBB", 25, "../resources/models/bomberBB/bomberBB.obj"),
    tree("tree", "../resources/models/Tree/tree.obj",
	 1, "../resources/models/TreeBB/TreeBB.obj"){
    
    renderer = &Renderer::getInstance("Avoid Enemy", 800, 600);
    renderer->cameraPosition = glm::vec3(0.0f, 10.0f, 0.0f);

    Image groundTexture("../resources/images/floor.png");
    renderer->generateTexture("ground", groundTexture);

    Image skyTexture("../resources/images/sky.png");
    renderer->generateTexture("sky", skyTexture);

    Image playerTexture("../resources/images/floor.png");
    renderer->generateTexture("playerTexture", playerTexture);

    Image treeTexture("../resources/models/Tree/tree.png");
    renderer->generateTexture("treeTexture", treeTexture);
    
    Image startScreenTexture("../resources/images/bom.png");
    renderer->generateTexture("startScreen", startScreenTexture);
    
    enemy.setFrameDelay(2);
    
    tree.offset = glm::vec3(2.6f, GROUND_Y, -8.0f);
    tree.rotation = glm::vec3(0.0f, -0.5f, 0.0f);
    
    gameState = START_SCREEN;
    
    startSeconds = 0;
    seconds = 0;
    
    lightModifier = -0.01f;

    // glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    MAX_Z = -1.0f;
    MIN_Z = -24.0f;
    
    GROUND_Y = -1.0f;
    FULL_ROTATION = 6.28f;// More or less 360 degrees in radians
    
    ENEMY_ROTATION_SPEED = 0.12f;
    ENEMY_SPEED = 0.08f;
    
    
    PLAYER_ROTATION_SPEED 0.12f;
    PLAYER_SPEED = 0.12f;
    
    // float deltaTime = 0.0f;	// time between current frame and last frame
    // float lastFrame = 0.0f;
  }
  
  void GameLogic::initGame() {
    player.offset = glm::vec3(1.0f, GROUND_Y, -4.0f);
    enemy.offset = glm::vec3(1.0f, GROUND_Y, -4.0f);
    
    enemy.startAnimating();
    
    enemyState = FLYING_STRAIGHT;
    enemyPreviousState = FLYING_STRAIGHT;
    enemyFramesInCurrentState = 1;
    
    startSeconds = glfwGetTime();
  }
  

  void GameLogic::moveCamera(const KeyInput &keyInput) {
    float cameraSpeed = PLAYER_SPEED;
    if(keyInput.camUp){
      std::cout << "camup pressed" << std::endl;
      renderer->cameraPosition += cameraSpeed * cameraFront;
    }
    if (keyInput.camDown) {
      std::cout << "camDown pressed" << std::endl;
      renderer->cameraPosition -= cameraSpeed * cameraFront;
    }
    if (keyInput.camLeft) {
      std::cout << "camLeft pressed" << std::endl;
      renderer->cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (keyInput.camRight) {
      std::cout << "camRight pressed" << std::endl;
      renderer->cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
  }
  void GameLogic::movePlayer(const KeyInput &keyInput) {
    player.stopAnimating();
    
    if (keyInput.left) {
      player.rotation.y -= PLAYER_ROTATION_SPEED;
      
      while (player.collidesWith(tree)) {
        player.rotation.y += PLAYER_ROTATION_SPEED;
      }
      
      if (player.rotation.y < -FULL_ROTATION)
        player.rotation.y = 0.0f;
      player.startAnimating();
      
    } else if (keyInput.right) {
      player.rotation.y += PLAYER_ROTATION_SPEED;
      while (player.collidesWith(tree)) {
        player.rotation.y -= PLAYER_ROTATION_SPEED;
      }
      
      
      if (player.rotation.y > FULL_ROTATION)
      player.rotation.y = 0.0f;
      player.startAnimating();
    }
    
    if (keyInput.up) {
      
      player.offset.x += sin(player.rotation.y) * PLAYER_SPEED;
      player.offset.z -= cos(player.rotation.y) * PLAYER_SPEED;
      
      while (player.collidesWith(tree)) {
        player.offset.x -= sin(player.rotation.y) * PLAYER_SPEED;
        player.offset.z += cos(player.rotation.y) * PLAYER_SPEED;
      }
      
      player.startAnimating();
      
    } else if (keyInput.down) {
      player.offset.x -= sin(player.rotation.y) * PLAYER_SPEED;
      player.offset.z += cos(player.rotation.y) * PLAYER_SPEED;
      
      while (player.collidesWith(tree)) {
        player.offset.x += sin(player.rotation.y) * PLAYER_SPEED;
        player.offset.z -= cos(player.rotation.y) * PLAYER_SPEED;
      }
      
      player.startAnimating();
    }
    
    if (player.offset.z < MIN_Z + 1.0f)
      player.offset.z = MIN_Z + 1.0f;
    if (player.offset.z > MAX_Z - 1.0f)
      player.offset.z = MAX_Z - 1.0f;
    
    if (player.offset.x < player.offset.z)
      player.offset.x = player.offset.z;
    if (player.offset.x > -(player.offset.z))
      player.offset.x = -(player.offset.z);
    
      player.animate();
    
    // Uncomment to see the player's view of the world
    // renderer->cameraPosition = player.offset;
    // renderer->cameraPosition.y += 1.0f;
    // renderer->cameraRotation = player.rotation;
    
  }
  
  void GameLogic::moveEnemy() {
    
    float xDistance = enemy.offset.x - player.offset.x;
    float zDistance = enemy.offset.z - player.offset.z;
    float distance = sqrt(xDistance * xDistance + zDistance * zDistance);
    
    float playerRelX = xDistance / distance;
    float playerRelZ = zDistance / distance;
    
    float enemyDirectionX = -sin(enemy.rotation.y);
    float enemyDirectionZ = cos(enemy.rotation.y);
    
    float dotPosDir = playerRelX * enemyDirectionX + playerRelZ * enemyDirectionZ; // dot product
    
    // enemy state: decide
    if (enemyState == enemyPreviousState) {
      ++enemyFramesInCurrentState;
    } else {
      enemyFramesInCurrentState = 1;
    }
    
    enemyPreviousState = enemyState;
    
    
    
    // Enemy state: represent
    
    enemy.rotation.x = 0;
    
    if (enemyState == TURNING) {
      
      enemy.rotation.y -= ENEMY_ROTATION_SPEED;
      
    }
    
    if (enemy.rotation.y < -FULL_ROTATION)
    enemy.rotation.y = 0.0f;
    
    
    enemy.offset.x += sin(enemy.rotation.y) * ENEMY_SPEED;
    enemy.offset.z -= cos(enemy.rotation.y) * ENEMY_SPEED;
    
    if (enemy.offset.z < MIN_Z)
      enemy.offset.z = MIN_Z;
    if (enemy.offset.z > MAX_Z)
      enemy.offset.z = MAX_Z;
    
    if (enemy.offset.x < enemy.offset.z)
      enemy.offset.x = enemy.offset.z;
    if (enemy.offset.x > -(enemy.offset.z))
      enemy.offset.x = -(enemy.offset.z);
    
    // Uncomment to see the bug's view of the world
    // renderer->cameraPosition = bug.offset;
    // renderer->cameraRotation = bug.rotation;
    
    enemy.animate();
  }
  
  void GameLogic::processGame(const KeyInput &keyInput) {
    moveCamera(keyInput);
    moveEnemy();
    movePlayer(keyInput);
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
      break;
    }
  }
  
  void GameLogic::render() {
    renderer->clearScreen();
    
    //Uncomment for groovy nightfall effect :)
    /* renderer->lightIntensity += lightModifier;
     
       if (renderer->lightIntensity < 0)
       {
       renderer->lightIntensity = 0.0f;
       lightModifier = 0.01f;
       }
     
       if (renderer->lightIntensity > 1.0f)
       {
       renderer->lightIntensity = 1.0f;
       lightModifier = -0.01f;
       } */
    
    if (gameState == START_SCREEN) {
      
      renderer->renderRectangle("startScreen", glm::vec3(-1.0f, 1.0f, 1.0f),
                              glm::vec3(1.0f, -1.0f, 1.0f));
      
      if (seconds != 0) {
        renderer->write("Enemy avoided " + intToStr(seconds) + " seconds",
                        glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(-0.95f, -0.6f), glm::vec2(0.0f, -0.8f));
      }
      
    } else {
      
      // Draw the sky
      renderer->renderRectangle("sky", glm::vec3(-1.0f, 1.0f, 1.0f),
                              glm::vec3(1.0f, -1.0f, 1.0f));
      
      // Draw the ground
      renderer->renderRectangle("ground", glm::vec3(-25.0f, GROUND_Y, MIN_Z),
                              glm::vec3(25.0f, GROUND_Y, MAX_Z), true);
      
      renderer->render(player, "playerTexture");
      renderer->render(enemy, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
      renderer->render(tree, "treeTexture");
      
    }
    renderer->swapBuffers();
  }
  
}