#pragma once

#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include "GLTexture.hpp"
#include <string>

namespace gameEngine {
	class Sprite {
		public:

			Sprite();
			~Sprite();

			void init(float x, float y, float width, float height, std::string texturePath);
			void draw();

		private:

			float _x;
			float _y;
			float _width;
			float _height;

			GLuint _vboID; //vertex buffer id

			GLTexture _texture;
	};
}