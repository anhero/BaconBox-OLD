#include "StringHelper.h"

using namespace RedBox;


std::wstring StringHelper::removeAll(wchar_t oldChar, const std::wstring& str) {
	std::wstring result;
	for (std::wstring::const_iterator i = str.begin(); i != str.end(); i++) {
		if (*i != oldChar) {
			result.append(1, *i);
		}
	}
	return result;
}