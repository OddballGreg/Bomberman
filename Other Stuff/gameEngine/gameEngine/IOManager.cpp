#include "IOManager.hpp"
#include <fstream>
#include <iostream>

#include "Log.hpp"
#include "Logger.hpp"

bool gameEngine::IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	// Log log("IOManager", "readFileToBuffer", CRITICAL);
	std::ifstream file(filePath, std::ios::binary);
	if(file.fail()) {
		std::cout << "IOManager file open error" << std::endl;
		return false;
	}

	// checks file size
	file.seekg(0, std::ios::end);
	unsigned int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	// this reduces file size by any header that might be at beginning
	fileSize -= (unsigned int)file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();
	return true;
}