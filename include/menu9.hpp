//
// Created by Gabriel GROENER on 2017/09/25.
//
#pragma once

class MenuScreen {

public:

	MenuScreen();
	MenuScreen(int width, int height, const char& windowName);
	MenuScreen(MenuScreen &obj) = default;
	~MenuScreen();

	MenuScreen &operator = (MenuScreen &obj) = default;

	void initializeMenu(int width, int height, const char* windowName);

};
