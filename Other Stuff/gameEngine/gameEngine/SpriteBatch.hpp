#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.hpp"
#include "Log.hpp"
#include "Logger.hpp"

namespace gameEngine {

	enum class GlyphSortType {
		NOTHING,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {
		GLuint	texture;
		float	depth;

		Vertex	topLeft;
		Vertex	bottomLeft;
		Vertex	topRight;
		Vertex	bottomRight;
	};

	class RenderBatch {
		public:
			RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture);
			GLuint offset;
			GLuint numVertices;
			GLuint texture;
	};

	class SpriteBatch {
		public:
			SpriteBatch();
			~SpriteBatch();

			void		init();
			void		begin(GlyphSortType sortType = GlyphSortType::TEXTURE); //default param
			void		draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Colour& colour);
			void		end();
			void		renderBatch();

		private:
			void		createRenderBatches();
			void		createVertexArray();
			void		sortGlyphs();

			static bool	compareFrontToBack(Glyph* a, Glyph* b);
			static bool	compareBackToFront(Glyph* a, Glyph* b);
			static bool	compareTexture(Glyph* a, Glyph* b);

			GLuint		_vbo;
			GLuint		_vao;

			GlyphSortType _sortType;
			std::vector<Glyph*> _glyphs;
			std::vector<RenderBatch> _renderBatches;
	};
}