#pragma once

#include "TextureCache.hpp"
#include <string>

namespace gameEngine {
    class ResourceManager {
        public:
            static GLTexture getTexture(std::string texturePath);


        private:
            static TextureCache _textureCache;

    };
}