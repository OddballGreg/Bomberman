#!/bin/bash

HOMEBREW="$HOME/.brew"

LIB_CMAKE="$HOME/.brew/Cellar/cmake"
LIB_PCKCONF="$HOME/.brew/Cellar/pkg-config"
LIB_PNG="$HOME/.brew/Cellar/libpng"
LIB_FREETYPE="$HOME/.brew/Cellar/freetype"
LIB_SDL="$HOME/.brew/Cellar/sdl"
LIB_SDL2="$HOME/.brew/Cellar/sdl2"
LIB_GLFW="$HOME/.brew/Cellar/glfw"
LIB_GLEW="$HOME/.brew/Cellar/glew"
LIB_GLM="$HOME/.brew/Cellar/glm"
LIB_SMFL="$HOME/.brew/Cellar/sfml"
LIB_EIGEN="$HOME/.brew/Cellar/eigen"

LIB_NANOGUI="../external/nanogui"

if [ ! -d "$HOMEBREW" ]; then
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
fi

if [ ! -d "$LIB_CMAKE" ]; then
	$HOME/.brew/bin/brew install cmake
fi

if [ ! -d "$LIB_PCKCONF" ]; then
	$HOME/.brew/bin/brew install pkg-config
fi

if [ ! -d "$LIB_PNG" ]; then
	$HOME/.brew/bin/brew install libpng
fi

if [ ! -d "$LIB_FREETYPE" ]; then
	$HOME/.brew/bin/brew install freetype
fi

if [ ! -d "$LIB_SDL" ]; then
	$HOME/.brew/bin/brew install sdl
fi

if [ ! -d "$LIB_SDL2" ]; then
	$HOME/.brew/bin/brew install sdl2
fi

if [ ! -d "$LIB_GLFW" ]; then
	$HOME/.brew/bin/brew install glfw
fi

if [ ! -d "$LIB_GLEW" ]; then
	$HOME/.brew/bin/brew install glew
fi

if [ ! -d "$LIB_GLM" ]; then
	$HOME/.brew/bin/brew install glm
fi


if [ ! -d "$LIB_SFML" ]; then
	$HOME/.brew/bin/brew install sfml
fi

if [ ! -d "$LIB_EIGEN" ]; then
	$HOME/.brew/bin/brew install eigen
fi

if [ ! -d "$LIB_NANOGUI" ]; then
	git clone --recursive https://github.com/wjakob/nanogui.git ../external/nanogui
	git submodule update --init --recursive
fi