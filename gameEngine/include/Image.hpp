#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Logger.hpp"
#include <png.h>

namespace gameEngine {

	/**
	 * @class	Image
	 *
	 * @brief	An image, loaded from a png file, which can be used for generating textures.
	 *
	 */

	class Image {
	private:

		unsigned long width, height;
		std::vector<float> imageData;
		unsigned long imageDataSize;

		void loadFromFile(const std::string fileLocation);

	public:

		/**
		 * @brief Default constructor
		 *
		 * @param fileLocation Location of the png image file
		 */
		Image(const std::string fileLocation = "");

		Image(const Image &obj);

		/**
		 * @brief Destructor
		 */
		~Image() = default;

		/**
		 * Overloaders
		 */
		Image operator = (const Image &obj);

		/**
		 * @brief Get the image width
		 * @return The image width
		 */
		unsigned long getWidth() const;

		/**
		 * @brief Get the image height
		 * @return The image height
		 */
		unsigned long getHeight() const;

		/**
		 * @brief Get the size of the image, in bytes
		 * @return Size of the image, in bytes
		 */
		unsigned long getByteSize() const;

		/**
		 * @brief Get the image data
		 * @return The image data
		 */
		const float* getData() const;

	};

}
