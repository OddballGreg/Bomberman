
#include <memory>
#include <stdexcept>
#include <iostream>
#include "../include/GameLogic.hpp"

using namespace gameEngine;

namespace Bomberman
{
	GameLogic::GameLogic(Settings *settings) : bomb("bomb", "../resources/models/bomberman/bomb.obj", 1, "../resources/models/bomberman/cube.obj"),
                                               _settings(settings), _maploader(settings) {

        profile_name = "test_profile_name";
        std::ifstream	profile("profiles/" + profile_name + ".profile");

        std::srand(std::time(0)); // use current time as seed for random generator

        if (!profile.is_open())
        {
            std::cout << "Creating New Profile: " << profile_name << std::endl;
            std::ofstream new_profile("profiles/" + profile_name + ".profile");
            new_profile << "0" << std::endl;
            new_profile.close();
            level = 0;
        }
        else
        {
            std::string buffer;
            std::getline(profile, buffer);
            std::string::size_type pos = buffer.find_last_not_of("\n \t");
            if(pos != std::string::npos)
                buffer = buffer.substr(0, pos+1);
            level = atoi(buffer.c_str()) % _settings->LEVEL_COUNT;
            profile.close();
        }

		_maploader.load_map(level);

		renderer = &Renderer::getInstance(settings, "BombermanTestV1", 0, 0, 1.2f);

		Image startScreenTexture("../resources/images/bom.png");
		renderer->generateTexture("startScreen", startScreenTexture);

		Image groundTexture("../resources/images/floor.png");
		renderer->generateTexture("groundTexture", groundTexture);

		Image objectTexture("../resources/images/green_canvas.png" );
		renderer->generateTexture("objectTexture", objectTexture);

        Image portalTexture("../resources/images/crate.png");
        renderer->generateTexture("portalTexture", portalTexture);

        Image skyTexture("../resources/images/sky.png");
		renderer->generateTexture("skyTexture", skyTexture);

		Image bombTexture("../resources/images/floor.png");
		renderer->generateTexture("bombTexture", bombTexture);

		Image enemyTexture("../resources/images/floor.png");
		renderer->generateTexture("enemyTexture", enemyTexture);

		 Image treeTexture("../resources/images/blue_canvas.png");
		 renderer->generateTexture("treeTexture", treeTexture);

		_maploader._player[0].setFrameDelay(1);
		gameState = START_SCREEN;
		seconds = 0;
		lightModifier = -0.01f;

		bombDropped = false;
		bombDelay = 100;
        bomb_radius = _settings->BOMB_RADIUS;

		// Initialise NanoGUI
//		_menu = new MenuScreen(renderer->getWindow());
//        _menu->renderMenu();

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
		delete (_settings);
	}

	void GameLogic::initGame()
    {
        bomb.offset = glm::vec3(0, 0, 0);
        _maploader._player[0].startAnimating();
        bomb.startAnimating();

		_maploader._player[0].startAnimating();

		renderer->cameraPosition.x = _maploader._player[0].offset.x;
		renderer->cameraPosition.y = 8;
		renderer->cameraPosition.z = (_maploader._player[0].offset.z) + 4;

		startSeconds = glfwGetTime();
	}

    void GameLogic::movePlayer(const KeyInput &keyInput)
    {
        _maploader._player[0].stopAnimating();

        if (keyInput.left)
        {
            glm::vec3 temp = _maploader._player[0].offset;
            temp.x -= _settings->PLAYER_SPEED;

            bool collision = false;
            for(int i = _maploader._walls.size() -1; i > -1; i--)
                if (temp.z < _maploader._walls[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._walls[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._walls[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._walls[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._obstacles.size() -1; i > -1; i--)
                if (temp.z < _maploader._obstacles[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._obstacles[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._obstacles[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._obstacles[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._enemies.size() -1; i > -1; i--)
                if (temp.z < _maploader._enemies[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._enemies[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._enemies[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._enemies[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            if (collision == false)
            {
                _maploader._player[0].rotation.y = 3 * (M_PI / 2) ;
                _maploader._player[0].offset.x -= _settings->PLAYER_SPEED;
            }
            _maploader._player[0].startAnimating();
        }
        else if (keyInput.right)
        {
            glm::vec3 temp = _maploader._player[0].offset;
            temp.x += _settings->PLAYER_SPEED;

            bool collision = false;
            for(int i = _maploader._walls.size() -1; i > -1; i--)
                if (temp.z < _maploader._walls[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._walls[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._walls[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._walls[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._obstacles.size() -1; i > -1; i--)
                if (temp.z < _maploader._obstacles[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._obstacles[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._obstacles[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._obstacles[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._enemies.size() -1; i > -1; i--)
                if (temp.z < _maploader._enemies[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._enemies[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._enemies[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._enemies[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            if (collision == false)
            {
                _maploader._player[0].rotation.y = M_PI / 2 ;
                _maploader._player[0].offset.x += _settings->PLAYER_SPEED;
            }
            _maploader._player[0].startAnimating();
        }

        if (keyInput.up)
        {
            glm::vec3 temp = _maploader._player[0].offset;
            temp.z -= _settings->PLAYER_SPEED;

            bool collision = false;
            for(int i = _maploader._walls.size() -1; i > -1; i--)
                if (temp.z < _maploader._walls[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._walls[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._walls[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._walls[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._obstacles.size() -1; i > -1; i--)
                if (temp.z < _maploader._obstacles[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._obstacles[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._obstacles[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._obstacles[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._enemies.size() -1; i > -1; i--)
                if (temp.z < _maploader._enemies[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._enemies[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._enemies[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._enemies[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            if (collision == false)
            {
                _maploader._player[0].rotation.y = 0;
                _maploader._player[0].offset.z -= _settings->PLAYER_SPEED;
            }
            _maploader._player[0].startAnimating();
        }
        else if (keyInput.down)
        {
            glm::vec3 temp = _maploader._player[0].offset;
            temp.z += _settings->PLAYER_SPEED;

            bool collision = false;
            for(int i = _maploader._walls.size() -1; i > -1; i--)
                if (temp.z < _maploader._walls[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._walls[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._walls[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._walls[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._obstacles.size() -1; i > -1; i--)
                if (temp.z < _maploader._obstacles[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._obstacles[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._obstacles[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._obstacles[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            for(int i = _maploader._enemies.size() -1; i > -1; i--)
                if (temp.z < _maploader._enemies[i].offset.z + _settings->COLLISION_ZONE
                    && temp.z > _maploader._enemies[i].offset.z - _settings->COLLISION_ZONE
                    && temp.x < _maploader._enemies[i].offset.x + _settings->COLLISION_ZONE
                    && temp.x > _maploader._enemies[i].offset.x - _settings->COLLISION_ZONE)
                    collision = true;

            if (collision == false)
            {
                _maploader._player[0].rotation.y = M_PI;
                _maploader._player[0].offset.z += _settings->PLAYER_SPEED;
            }
            _maploader._player[0].startAnimating();
        }

        // Keep Player On Map
        if (_maploader._player[0].offset.z > _settings->MAX_Z)
            _maploader._player[0].offset.z = _settings->MAX_Z;
        if (_maploader._player[0].offset.z < _settings->MIN_Z)
            _maploader._player[0].offset.z = _settings->MIN_Z;
        if (_maploader._player[0].offset.x > _settings->MAX_X)
            _maploader._player[0].offset.x = _settings->MAX_X;
        if (_maploader._player[0].offset.x < _settings->MIN_X)
            _maploader._player[0].offset.x = _settings->MIN_X;


        if (keyInput.camRotXUp)
            renderer->cameraRotation.x += cos(_maploader._player[0].rotation.y) * 0.05f;
        else if (keyInput.camRotXDown)
            renderer->cameraRotation.x -= cos(_maploader._player[0].rotation.y) * 0.05f;
        else if (keyInput.camRotYUp)
            renderer->cameraRotation.y += cos(_maploader._player[0].rotation.y) * 0.05f;
        else if (keyInput.camRotYDown)
            renderer->cameraRotation.y -= cos(_maploader._player[0].rotation.y) * 0.05f;
        else if (keyInput.camRotZUp)
            renderer->cameraRotation.z += cos(_maploader._player[0].rotation.y) * 0.05f;
        else if (keyInput.camRotZDown)
            renderer->cameraRotation.z -= cos(_maploader._player[0].rotation.y) * 0.05f;
        else if (keyInput.camPosXUp)
            renderer->cameraPosition.x += 0.5f;
        else if (keyInput.camPosXDown)
            renderer->cameraPosition.x -= 0.5f;
        else if (keyInput.camPosYUp)
            renderer->cameraPosition.y += 0.5f;
        else if (keyInput.camPosYDown)
            renderer->cameraPosition.y -= 0.5f;
        else if (keyInput.camPosZUp)
            renderer->cameraPosition.z += 0.5f;
        else if (keyInput.camPosZDown)
            renderer->cameraPosition.z -= 0.5f;

        _maploader._player[0].animate();

        if (keyInput.space && !bombDropped)
        {
            bombDropped = true;
            bomb.offset = _maploader._player[0].offset;
            bomb.startAnimating();
        }

        renderer->cameraPosition.x = 0.0f;
        renderer->cameraPosition.z = 11.32f;
        renderer->cameraPosition.y = 16.0f;
        renderer->cameraRotation.x = 1.1f;

    }

    void GameLogic::processGame(const KeyInput &keyInput)
    {
        movePlayer(keyInput);

        // This code determines if an enemy is colliding with something and prevents them from moving
        // Move it to the enemy class at a later stage, modify behaviour to turn
        for(int i = _maploader._enemies.size() - 1; i > -1; i--)
            _maploader._enemies[i].move(&_maploader, i);

    }

	void GameLogic::processStartScreen(const KeyInput &keyInput)
	{
		if (keyInput.enter)
		{
			initGame();
			gameState = PLAYING;
		}
	}

	void GameLogic::process(const KeyInput &keyInput)
	{
		switch (gameState)
		{
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

	void GameLogic::render()
	{
//        _menu->renderMenu(); //uncomment this for menu
		renderer->clearScreen();
//        _menu->menuHandler();

		if (gameState == START_SCREEN)
		{
			renderer->renderRectangle("skyTexture", glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f));
			renderer->renderRectangle("startScreen", glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f));
            // MenuScreen mainscreenMenu(window); //store as a pointer and add to main loop
            // mainscreenMenu.mainMenu();
//            _menu->renderMenu(); //uncomment this for menu
//            MenuScreen menuSetttings;
//            menuSetttings.initializeMenu(renderer->getWindow());
//            _menu->menuHandler();
		}
		else
		{
			renderer->renderRectangle("skyTexture", glm::vec3(-1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, -1.0f, 1.0f));

			if (seconds != 0)
			{
				renderer->write("Enemy avoided for " + intToStr(seconds) + " seconds",
				glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(-0.95f, -0.6f), glm::vec2(0.0f, -0.8f));
			}
			// Draw the background

			renderer->renderRectangle("groundTexture", glm::vec3(_settings->MIN_X, _settings->GROUND_Y, _settings->MIN_Z),
				glm::vec3(_settings->MAX_X, _settings->GROUND_Y, _settings->MAX_Z), true);

			for(int i = _maploader._walls.size() -1; i > -1; i--)
				renderer->render(_maploader._walls[i], "groundTexture");

			for(int i = _maploader._obstacles.size() -1; i > -1; i--)
				renderer->render(_maploader._obstacles[i], "objectTexture");

			for(int i = _maploader._player.size() -1; i > -1; i--)
				renderer->render(_maploader._player[i], "objectTexture");

			for(int i = _maploader._enemies.size() -1; i > -1; i--)
				renderer->render(_maploader._enemies[i], "enemyTexture");

            for(int i = _maploader._powerups.size() -1; i > -1; i--)
                renderer->render(_maploader._powerups[i], "treeTexture");

            if (can_leave == true)
                renderer->render(_maploader._portal[0], "portalTexture");
            else
                renderer->render(_maploader._portal[1], "portalTexture");

            //Check if player enters portal, load next level
            if (can_leave
                && _maploader._portal[0].offset.z < _maploader._player[0].offset.z + _settings->COLLISION_ZONE
                && _maploader._portal[0].offset.z > _maploader._player[0].offset.z - _settings->COLLISION_ZONE
                && _maploader._portal[0].offset.x < _maploader._player[0].offset.x + _settings->COLLISION_ZONE
                && _maploader._portal[0].offset.x > _maploader._player[0].offset.x - _settings->COLLISION_ZONE) {
                level++;
                std::ofstream profile("profiles/" + profile_name + ".profile");
                profile << std::to_string(level) << std::endl;
                profile.close();

                //To make a player win in the end.
//                if (level > _settings->LEVEL_COUNT)
//                    open menu.
//                else
//                {
                _maploader.load_map(level % _settings->LEVEL_COUNT);
                can_leave = false;
                bomb_radius = _settings->BOMB_RADIUS;
//               }
            }

            if (bombDropped && bombDelay != 0) {
                renderer->render(bomb, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
                bombDelay--;
            }
            else if (bombDelay == 0)
            {
                bombDropped = false;
                bombDelay = 100;

                // Blow stuff up here
                for(long i = _maploader._obstacles.size() -1; i > -1; i--) {
                    if (bomb.offset.z < _maploader._obstacles[i].offset.z + bomb_radius
                        && bomb.offset.z > _maploader._obstacles[i].offset.z - bomb_radius
                        && bomb.offset.x < _maploader._obstacles[i].offset.x + _settings->BOMB_COLLUMN
                        && bomb.offset.x > _maploader._obstacles[i].offset.x - _settings->BOMB_COLLUMN) {
                        if (std::rand() % 101 > _settings->POWERUP_CHANCE ) {
                            gameEngine::SceneObject temp2(*_maploader._powerup_template);
                            temp2.offset = _maploader._obstacles[i].offset;
                            _maploader._powerups.push_back(temp2);
                        }
                        _maploader._obstacles.erase(_maploader._obstacles.begin() + i);
                        i = _maploader._obstacles.size() -1;
                    } else if (bomb.offset.x < _maploader._obstacles[i].offset.x + bomb_radius
                         && bomb.offset.x > _maploader._obstacles[i].offset.x - bomb_radius
                         && bomb.offset.z < _maploader._obstacles[i].offset.z + _settings->BOMB_COLLUMN
                         && bomb.offset.z > _maploader._obstacles[i].offset.z - _settings->BOMB_COLLUMN) {
                        _maploader._obstacles.erase(_maploader._obstacles.begin() + i);
                        i = _maploader._obstacles.size() -1;
                        if (_settings->PLAY_SOUND) {
                            destroyedObject.initialize("../SoundEngine/music/box_falls.wav");
                            destroyedObject.play(false);
                        }
                    }
                }

                for(long i = _maploader._enemies.size() -1; i > -1; i--) {
                    if (bomb.offset.z < _maploader._enemies[i].offset.z + bomb_radius
                        && bomb.offset.z > _maploader._enemies[i].offset.z - bomb_radius
                        && bomb.offset.x < _maploader._enemies[i].offset.x + _settings->BOMB_COLLUMN
                        && bomb.offset.x > _maploader._enemies[i].offset.x - _settings->BOMB_COLLUMN) {
                        _maploader._enemies.erase(_maploader._enemies.begin() + i);
                        i = _maploader._enemies.size() -1;
                        if (_settings->PLAY_SOUND) {
                            enemykilled.initialize("../SoundEngine/music/GameOverArcade.wav");
                            enemykilled.play(false);
                        }
                    } else if (bomb.offset.x < _maploader._enemies[i].offset.x + bomb_radius
                           && bomb.offset.x > _maploader._enemies[i].offset.x - bomb_radius
                           && bomb.offset.z < _maploader._enemies[i].offset.z + _settings->BOMB_COLLUMN
                           && bomb.offset.z > _maploader._enemies[i].offset.z - _settings->BOMB_COLLUMN) {
                        _maploader._enemies.erase(_maploader._enemies.begin() + i);
                        i = _maploader._enemies.size() -1;
                        if (_settings->PLAY_SOUND) {
                            enemykilled.initialize("../SoundEngine/music/GameOverArcade.wav");
                            enemykilled.play(false);
                        }
                    }
                }

                if (bomb.offset.z < _maploader._player[0].offset.z + bomb_radius
                    && bomb.offset.z > _maploader._player[0].offset.z - bomb_radius
                    && bomb.offset.x < _maploader._player[0].offset.x + _settings->BOMB_COLLUMN
                    && bomb.offset.x > _maploader._player[0].offset.x - _settings->BOMB_COLLUMN) {
                    _maploader.load_map(level);
                }
                else if (bomb.offset.x < _maploader._player[0].offset.x + bomb_radius
                         && bomb.offset.x > _maploader._player[0].offset.x - bomb_radius
                         && bomb.offset.z < _maploader._player[0].offset.z + _settings->BOMB_COLLUMN
                         && bomb.offset.z > _maploader._player[0].offset.z - _settings->BOMB_COLLUMN)
                    _maploader.load_map(level);


                 

                if (_maploader._enemies.size() == 0)
                    can_leave = true;
			}

        }
		renderer->swapBuffers();
	}
}
