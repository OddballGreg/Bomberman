#pragma once
#include "GLTexture.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

namespace gameEngine {
    class ImageLoader {
        public:
            static GLTexture loadPNG(std::string filePath);
    };
}