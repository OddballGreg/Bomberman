Since the path for Homebrew is different on our Macs at school
you need to run INSTALL.sh before running cmake.

mkdir build
cd build
cmake ../ -G "Unix Makefiles"
make
./bomberman


Stuff still needs to be added to the gitignore for the cmake stuff. But for everyone to use the same build I am just leaving it for now.

The build directory and the external/nanogui directory should be ignored