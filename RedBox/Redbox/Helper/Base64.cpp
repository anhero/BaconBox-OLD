#include "Base64.h"

#include <cctype>

namespace RedBox {
	const std::string BASE_64_CHARS("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

	bool isBase64(std::string::value_type c);

	bool Base64::decode(const std::string &data, std::string &result) {
		bool success = true;

		unsigned char charArray3[3];
		unsigned char charArray3[4];

		for (std::string::size_type inputSize = data.size(); inputSize > 0;
		     --inputSize) {
		}

		return success;
	}

	bool isBase64(std::basic_string::value_type c) {
		return isalnum(c) || c == '+' || c == '/';
	}
}
