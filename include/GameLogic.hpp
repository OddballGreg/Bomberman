#pragma once

#include <memory>
#include "../gameEngine/include/Logger.hpp"
#include "../gameEngine/include/SceneObject.hpp"
#include "../gameEngine/include/Renderer.hpp"
#include "../gameEngine/include/Enemy.hpp"
#include "../gameEngine/include/Menu.hpp"
#include "../include/MapLoader.hpp"
#include "../SoundEngine/SoundEngine.hpp"
#include "../include/Settings.hpp"

#include <nanogui/nanogui.h>
#include "KeyInput.hpp"

using namespace gameEngine;

namespace Bomberman {
	class GameLogic {

	private:

		MapLoader _maploader;
		SceneObject bomb;
		Sound explosion;
		Settings *_settings;
		int level;

		enum GameState {
			START_SCREEN,
			PLAYING
		};

		GameState gameState;

		double startSeconds;
		int seconds;

		void initGame();
		void processGame(const KeyInput &keyInput);
		void processStartScreen(const KeyInput &keyInput);
		void movePlayer(const KeyInput &keyInput);

		bool bombDropped;
		int	 bombDelay;

	public:

		Screen *_screen = nullptr;
		Renderer *renderer = nullptr;

		GameLogic(Settings *settings);
		~GameLogic();

		void setScreen(Screen *screen);
		void process(const KeyInput &keyInput);
		void render();

		float lightModifier;
	};

}

