#include "TextureCache.hpp"
#include "ImageLoader.hpp"
#include <iostream>

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::TextureCache::TextureCache() {
	// Log log("TextureCache", "TextureCache", CRITICAL);
}

gameEngine::TextureCache::~TextureCache() {
	// Log log("TextureCache", "~TextureCache", CRITICAL);
}

gameEngine::GLTexture gameEngine::TextureCache::getTexture(std::string texturePath) {
	// check if texture is in the map
	// Log log("TextureCache", "getTexture", CRITICAL);
	std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
	
	// or
	// auto mit = _textureMap.find(texturePath);

	if (mit == _textureMap.end()) {
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		// if it doesnt exist add it to the map
		_textureMap.insert(make_pair(texturePath, newTexture));

		// std::cout << "Loaded texture" << std::endl;
		return newTexture;
	}

	// std::cout << "Used cached texture" << std::endl;
	// returns second element of the pair
	return mit->second;
}