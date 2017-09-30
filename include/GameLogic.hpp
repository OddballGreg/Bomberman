#pragma once

#include <memory>
#include <math.h>
#include <fstream>
#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Renderer.hpp"
#include "../gameEngine/include/Enemy.hpp"
#include "../gameEngine/include/Menu.hpp"
#include "../include/MapLoader.hpp"
#include "../SoundEngine/SoundEngine.hpp"
#include "../include/Settings.hpp"

#include "menu.hpp"
#include <nanogui/nanogui.h>
#include "KeyInput.hpp"

using namespace gameEngine;


class	MenuScreen;

namespace Bomberman {
	class GameLogic {

	private:

		MapLoader	_maploader;
		SceneObject	bomb;
		Sound		explosion;
		Settings	*_settings;

		int 		level;
		double		startSeconds;
		int			seconds;
		bool		bombDropped;
		int			bombDelay;
		bool		can_leave = false;
		float		bomb_radius;
		int			explosion_time = 0;

		enum GameState {
			START_SCREEN,
			PLAYING
		};

		GameState	gameState;
		MenuScreen *_menu;

		void initGame();
		void processGame(const KeyInput &keyInput);
		void processStartScreen(const KeyInput &keyInput);
		void movePlayer(const KeyInput &keyInput);

	public:

		Screen *_screen = nullptr;
		Renderer *renderer = nullptr;
		std::string profile_name;

		GameLogic(Settings *settings);
		GameLogic(GameLogic &obj) = default;
		~GameLogic();

		GameLogic &operator = (GameLogic &obj) = default;

		void setScreen(Screen *screen);
		void process(const KeyInput &keyInput);
		void render();

		float lightModifier;
	};

}

