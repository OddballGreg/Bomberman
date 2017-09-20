#pragma once

#include <string>
#include <vector>

namespace gameEngine {

  /**
   * @brief Separates a string into tokens, using the given character
   * as a separator
   *
   * @param input The input string
   * @param sep	The separator
   * @param [in,out] tokens The tokens
   *
   * @return The number of tokens
   */

  int getTokens(const std::string input, const char sep, std::vector<std::string> &tokens);
}
