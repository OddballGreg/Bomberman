#include "../include/GetTokens.hpp"

namespace gameEngine {

	int getTokens(const std::string input, const char sep, std::vector<std::string> &tokens) {
		size_t curPos = 0;
		int count = 0;

		size_t length = input.length();

		for (size_t idx = 0; idx < length; ++idx) {
			if (input[idx] == sep)
				++count;
		}
		++count;

		for (int idx = 0; idx < count; ++idx) { // last one
			if (idx == count - 1) {
				tokens.push_back(input.substr(curPos));
			}
			else {
				size_t foundPos = input.find(sep, curPos);
				tokens.push_back(input.substr(curPos, foundPos - curPos));
				curPos = foundPos + 1;
			}
		}
		return count;
	}
}
