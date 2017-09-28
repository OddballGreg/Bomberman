//
// Created by Gabriel GROENER on 2017/09/25.
//
#pragma once

class MenuScreen {

public:

	MenuScreen();
	MenuScreen(int width, int height, const char& windowName);
	~MenuScreen();

	void initializeMenu(int width, int height, const char* windowName);

};
