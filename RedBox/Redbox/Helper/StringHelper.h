/**
 * @file
 * @ingroup Helper
 */
#ifndef __STRINGHELPER_H
#define __STRINGHELPER_H
#include <string>

#define MINIMUM_CHARCODE 32

namespace RedBox{ 
	/**
	 * String utilities. Class containing functions used work with strings.
	 * @ingroup Helper
	 */
	class StringHelper {
	public:
		/**
		 * Removes all occurrences of a character.
		 * @param oldChar Character to remove from the string.
		 * @param str String in which all occurrences of the received character
		 * will be deleted.
		 */
		static std::wstring removeAll(wchar_t oldChar, const std::wstring& str);
	};
}

#endif
