Since the path for Homebrew is different on our Macs at school
you need to run INSTALL.sh before running cmake.

mkdir build
cd build
cmake ../ -G "Unix Makefiles"
make
./bomberman
