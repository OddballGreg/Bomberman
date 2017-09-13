#!/bin/sh

mkdir dependencies
cd dependencies
git clone --recursive git@github.com:wjakob/nanogui.git
brew install cmake xorg-dev libglu1-mesa-dev
brew install python-dev
mkdir build
cd build
cmake ../
make
