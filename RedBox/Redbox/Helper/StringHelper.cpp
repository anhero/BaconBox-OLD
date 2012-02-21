#include "StringHelper.h"

#include <algorithm>
#include <functional>
#include <locale>

namespace RedBox {

	std::wstring StringHelper::removeAll(wchar_t oldChar, const std::wstring &str) {
		std::wstring result;

		for (std::wstring::const_iterator i = str.begin(); i != str.end(); ++i) {
			if (*i != oldChar) {
				result.append(1, *i);
			}
		}

		return result;
	}

	std::string &StringHelper::trim(std::string &str) {
		return leftTrim(rightTrim(str));
	}

	std::string &StringHelper::leftTrim(std::string &str) {
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return str;
	}

	std::string &StringHelper::rightTrim(std::string &str) {
		str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
		return str;
	}
}
