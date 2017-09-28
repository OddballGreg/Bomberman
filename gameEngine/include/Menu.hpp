#pragma once

#include <nanogui/nanogui.h>
#include <iostream>

using namespace nanogui;

class Menu {

public:
	enum test_enum {
		Item1 = 0,
		Item2,
		Item3
	};

	bool bvar = true;
	int ivar = 12345678;
	double dvar = 3.1415926;
	float fvar = (float)dvar;
	std::string strval = "A string";
	test_enum enumval = Item2;

	Menu(Screen *screen);
	~Menu();
};