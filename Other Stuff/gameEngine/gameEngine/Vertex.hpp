#pragma once
#include <GL/glew.h>

namespace gameEngine {
	struct		Position {
		float	x;
		float	y;
	};

	struct		UV {
		float	u;
		float	v;
	};

	struct		Colour {
		GLubyte	r;
		GLubyte	g;
		GLubyte	b;
		GLubyte	a;
	};

	struct Vertex {

		Position	position;
		Colour		colour;
		UV			uv;

		void		setColour(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
		void		setUV(float u, float v);
		void		setPosition(float x, float y);
	};
}
