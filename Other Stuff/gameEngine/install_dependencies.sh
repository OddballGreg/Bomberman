#!/bin/sh

mkdir dependencies
cd dependencies
git clone https://github.com/wjakob/nanogui.git --recursive .nanogui
brew install cmake
brew install python
mkdir cmake-build-debug
cd cmake-build-debug
cmake ../
make
