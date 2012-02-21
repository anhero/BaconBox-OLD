#include "Base64.h"

#include <cctype>

namespace RedBox {
	const std::string BASE_64_CHARS("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

	unsigned char BASE_64_INDEXES[80] = {
		62, -1, -1, -1, 63, 52, 53, 54, 55, 56,
		57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
		-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
		36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
		46, 47, 48, 49, 50, 51
	};


	bool isBase64(std::string::value_type c);

	void Base64::decode(const std::string &data, std::string &result) {
		result.clear();

		unsigned char charArray3[3];
		unsigned char charArray4[4];

		std::string::size_type in = 0;
		std::string::size_type inputSize = data.size();
		unsigned int i = 0;

		while (inputSize-- && data[in] != '=' && isBase64(data[in])) {
			charArray4[i++] = data[in];
			++in;

			if (i == 4) {
				for (i = 0; i < 4; ++i) {
					charArray4[i] = BASE_64_INDEXES[charArray4[i] - '+'];
					//charArray4[i] = BASE_64_CHARS.find(charArray4[i]);
				}

				charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
				charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
				charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];

				for (i = 0; i < 3; ++i) {
					result.append(1, charArray3[i]);
				}

				i = 0;
			}
		}

		if (i) {
			for (unsigned int j = i; j < 4; ++j) {
				charArray4[j] = 0;
			}

			for (unsigned int j = 0; j < 4; ++j) {
				charArray4[j] = (charArray4[j] == 0) ? (-1) : (BASE_64_INDEXES[charArray4[j] - '+']);
				//charArray4[j] = BASE_64_CHARS.find(charArray4[j]);
			}

			charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
			charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
			charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];

			for (unsigned int j = 0; j < i - 1; ++j) {
				result.append(1, charArray3[j]);
			}
		}
	}

	bool isBase64(std::string::value_type c) {
		return isalnum(c) || c == '+' || c == '/';
	}
}
