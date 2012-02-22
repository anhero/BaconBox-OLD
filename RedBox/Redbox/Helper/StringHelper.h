/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_STRINGHELPER_H
#define RB_STRINGHELPER_H

#include <algorithm>
#include <string>

#define MINIMUM_CHARCODE 32

namespace RedBox {
	/**
	 * String utilities. Class containing functions used work with strings.
	 * @ingroup Helper
	 */
	class StringHelper {
	private:
		template <typename ValueType>
		struct IsChar {
			IsChar(ValueType newCharValue) : charValue(newCharValue) {}
			bool operator()(ValueType toCheck) const {
				return charValue == toCheck;
			}
			ValueType charValue;
		};
	public:
		/**
		 * Removes all occurences of a character.
		 * @param toRemove Character to remove from the string.
		 * @param str String to have the specified character removed.
		 * @tparam ValueType Type of the
		 */
		template <typename ValueType>
		static void removeAll(ValueType toRemove,
		                      std::basic_string<ValueType> &str) {
			str.erase(std::remove_if(str.begin(), str.end(), IsChar<ValueType>(toRemove)));
		}

		/**
		 * Trims white spaces at the beginning and the end of a string.
		 * @param str String to trim. Will be modified.
		 * @return Trimmed string.
		 */
		static std::string &trim(std::string &str);

		/**
		 * Trims white spaces at the beginning of a string.
		 * @param str String to trim. Will be modified.
		 * @return Trimmed string.
		 */
		static std::string &leftTrim(std::string &str);

		/**
		 * Trims white spaces at the end of a string.
		 * @param str String to trim. Will be modified.
		 * @return Trimmed string.
		 */
		static std::string &rightTrim(std::string &str);

		/**
		 * Tokenizes a string.
		 * @param str String to tokenize.
		 * @param tokens Container in which to put the tokens.
		 * @param delimiters The string to use as the delimiter.
		 * @param trimEmpty Set to true if you want the empty tokens to be
		 * ignored.
		 */
		template <typename ContainerType>
		static void tokenize(const std::string &str, ContainerType &tokens,
		                     const std::string delimiters = std::string(),
		                     bool trimEmpty = false) {
			typedef ContainerType Base;
			typedef typename Base::value_type ValueType;
			typedef typename ValueType::size_type SizeType;

			std::string::size_type position;
			std::string::size_type lastPosition = 0;

			while (true) {
				position = str.find_first_of(delimiters, lastPosition);

				if (position == std::string::npos) {
					position = str.length();

					if (position != lastPosition || !trimEmpty) {
						tokens.push_back(ValueType(&str[0] + lastPosition,
						                           static_cast<SizeType>(position - lastPosition)));
					}

					break;

				} else {
					if (position != lastPosition || !trimEmpty) {
						tokens.push_back(ValueType(&str[0] + lastPosition,
						                           static_cast<SizeType>(position - lastPosition)));
					}
				}

				lastPosition = position + 1;
			}
		}
	};
}

#endif
