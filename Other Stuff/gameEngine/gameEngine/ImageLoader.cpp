#include "ImageLoader.hpp"
#include "picoPNG.hpp"
#include "IOManager.hpp"

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::GLTexture gameEngine::ImageLoader::loadPNG(std::string filePath) {
	// Log log("ImageLoader", "loadPNG", CRITICAL);
	GLTexture texture = {};

	std::vector<unsigned char> out;
	unsigned long width;
	unsigned long height;

	std::vector<unsigned char> in;

	if (IOManager::readFileToBuffer(filePath, in) == false) {
		std::cout << "Failed to load png to buffer" << std::endl;
	}

	int errorCode = decodePNG(out, width, height, &in[0], in.size());

	if (errorCode != 0) {
		std::cout << "decodePNG failed with error " << std::to_string(errorCode) << std::endl;
	}

	glGenTextures(1, &(texture.id));

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}