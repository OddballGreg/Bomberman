#!/bin/bash

HOMEBREW="$HOME/.brew"

LIB_CMAKE="$HOME/.brew/Cellar/cmake"
LIB_PCKCONF="$HOME/.brew/Cellar/pkg-config"
LIB_PNG="$HOME/.brew/Cellar/libpng"
LIB_FREETYPE="$HOME/.brew/Cellar/freetype"
LIB_SDL="$HOME/.brew/Cellar/sdl"
LIB_SDL2="$HOME/.brew/Cellar/sdl2"
LIB_GLFW="$HOME/.brew/Cellar/glfw"
LIB_GLEW="$HOME/.brew/Cellalsr/glew"
LIB_SMFL="$HOME/.brew/Cellar/sfml"
LIB_EIGEN="$HOME/.brew/Cellar/eigen"

if [ ! -d "$HOMEBREW" ]; then
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
fi

if [ ! -d "$LIB_CMAKE" ]; then
	brew install cmake
fi

if [ ! -d "$LIB_PCKCONF" ]; then
	brew install pkg-config
fi

if [ ! -d "$LIB_PNG" ]; then
	brew install libpng
fi

if [ ! -d "$LIB_FREETYPE" ]; then
	brew install freetype
fi

if [ ! -d "$LIB_SDL" ]; then
	brew install sdl
fi

if [ ! -d "$LIB_SDL2" ]; then
	brew install sdl2
fi

if [ ! -d "$LIB_GLFW" ]; then
	brew install glfw
fi

if [ ! -d "$LIB_GLEW" ]; then
	brew install glew
fi

if [ ! -d "$LIB_SFML" ]; then
	brew install sfml
fi

if [ ! -d "$LIB_EIGEN" ]; then
	brew install eigen
fi