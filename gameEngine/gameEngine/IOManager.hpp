#pragma once

#include <vector>
#include <iostream>

namespace gameEngine {
		class IOManager {
				public:
						static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

		};
}
