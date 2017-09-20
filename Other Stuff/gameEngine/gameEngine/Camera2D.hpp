#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gameEngine {
	class Camera2D {
		public:
			Camera2D();
			~Camera2D();

			void		init(int width, int height);
			void		update();
			void		setPosition(const glm::vec2& newPosition);
			glm::vec2	getPosition();
			void		setScale(float newScale);
			float		getScale();
			glm::mat4	getCameraMatrix();
			glm::vec2	convertScreenToWorld(glm::vec2 screenCoords);

		private:
			int			_width;
			int			_height;
			bool		_needsMatrixUpdate;
			float		_scale;

			glm::vec2	_position;
			glm::mat4	_cameraMatrix;
			glm::mat4	_orthoMatrix;
	};
}