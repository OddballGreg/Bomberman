#include "Vertex.hpp"

#include "Log.hpp"
#include "Logger.hpp"

void gameEngine::Vertex::setColour(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	// Log log("Vertex", "setColour", CRITICAL);
	colour.r = r;
	colour.g = g;
	colour.b = b;
	colour.a = a;
}

void gameEngine::Vertex::setUV(float u, float v) {
	// Log log("Vertex", "setUV", CRITICAL);
	uv.u = u;
	uv.v = v;
}

void gameEngine::Vertex::setPosition(float x, float y) {
	// Log log("Vertex", "setPosition", CRITICAL);
	position.x = x;
	position.y = y;
}