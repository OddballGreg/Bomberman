#pragma once

#include <memory>
#include <math.h>
#include <fstream>
#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Renderer.hpp"
#include "../gameEngine/include/Enemy.hpp"
#include "../include/MapLoader.hpp"
#include "../SoundEngine/SoundEngine.hpp"
#include "../include/Settings.hpp"

#include "KeyInput.hpp"

using namespace gameEngine;


class	MenuScreen;

namespace Bomberman {
	class GameLogic {

	private:

		MapLoader	_maploader;
		SceneObject	bomb;
		Sound		explosion;
        Sound		enemykilled;
        Sound		destroyedObject;
		Settings	*_settings;

		int 		level;
		double		startSeconds;
		int			seconds;
		bool		bombDropped;
		int			bombDelay;
        bool        can_leave = false;
        float       bomb_radius;

		enum GameState {
			START_SCREEN,
			PLAYING
		};

		GameState	gameState;

		void initGame();
		void processGame(const KeyInput &keyInput);
		void processStartScreen(const KeyInput &keyInput);
		void movePlayer(const KeyInput &keyInput);

	public:

		Renderer *renderer = nullptr;
		std::string profile_name;

		GameLogic(Settings *settings);
		GameLogic(GameLogic &obj) = default;
		~GameLogic();

		GameLogic &operator = (GameLogic &obj) = default;

		void process(const KeyInput &keyInput);
		void render();

		float lightModifier;
	};

}

