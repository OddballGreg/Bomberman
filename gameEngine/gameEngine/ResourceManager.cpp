#include "ResourceManager.hpp"

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::TextureCache gameEngine::ResourceManager::_textureCache;

gameEngine::GLTexture gameEngine::ResourceManager::getTexture(std::string texturePath) {
    // Log log("ResourceManager", "getTexture", CRITICAL);
    return _textureCache.getTexture(texturePath);
}