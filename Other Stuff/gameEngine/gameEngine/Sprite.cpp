#include "Sprite.hpp"
#include "Vertex.hpp"
#include "ResourceManager.hpp"

#include <cstddef>
#include <string>

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::Sprite::Sprite() {
	// Log log("Sprite", "Sprite", CRITICAL);
	_vboID = 0;
}

gameEngine::Sprite::~Sprite() {
	// Log log("Sprite", "~Sprite", CRITICAL);
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void gameEngine::Sprite::init(float x, float y, float width, float height, std::string texturePath) {
	// Log log("Sprite", "init", CRITICAL);
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_texture = ResourceManager::getTexture(texturePath);

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	// making a quad: 2 triangles
	// first triangle

	vertexData[0].setPosition(x + width, y + width);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(x, y + width);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	// second triangle

	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(x + width, y + width);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		vertexData[i].setColour(255, 0, 255, 255);
	}
	vertexData[1].setColour(0, 255, 0, 255);
	vertexData[4].setColour(255, 0, 0, 255);
	vertexData[5].setColour(255, 0, 255, 255);


	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gameEngine::Sprite::draw() {
	// Log log("Sprite", "draw", CRITICAL);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	// glEnableVertexAttribArray(2);

	// // This is the position attribute
	// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// // this is the colour attribute
	// glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	// // this is the uv attribute
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //free after use
}