#pragma once
/*
    src/example2.cpp -- C++ version of an example application that shows
    how to use the form helper class. For a Python implementation, see
    '../python/example2.py'.
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.
    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/nanogui.h>
#include <iostream>
#include <GLFW/glfw3.h>

using namespace nanogui;

class Menu {

public:
    // enum test_enum {
    //     Item1 = 0,
    //     Item2,
    //     Item3
    // };
    
    // bool bvar = true;
    // int ivar = 12345678;
    // double dvar = 3.1415926;
    // float fvar = (float)dvar;
    // std::string strval = "A string";
    // test_enum enumval = Item2;
    // //Color colval(0.5f, 0.5f, 0.7f, 1.f);
    
    

    Menu(GLFWwindow *window);
	~Menu();
};