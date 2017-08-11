#include "FatalError.hpp"
#include <string>

void FatalError::fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
}