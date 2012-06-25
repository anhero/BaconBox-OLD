/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_STRINGHELPER_H
#define RB_STRINGHELPER_H

#include <cctype>

#include <algorithm>
#include <string>
#include <sstream>
#include <ios>
#include <functional>
#include <locale>

#define MINIMUM_CHARCODE 32

namespace BaconBox {
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
		 * Converts a string to a numeric.
		 * @param str String to read the number from.
		 * @param value Value in which to put the output.
		 * @param numericBase Numeric base to use to convert the string to the
		 * numeric.
		 */
		template <typename ValueType, typename CharType>
		static bool fromString(const std::basic_string<CharType> &str,
							   ValueType &value,
							   std::ios_base &(*numericBase)(std::ios_base&) = std::dec) {
			return !(std::istringstream(str) >> numericBase >> value).fail();
		}
		
		/**
		 * Converts a string to lower case.
		 * @param str String to have its case lowered.
		 * @return String in all lower case.
		 */
		template <typename CharType>
		static std::basic_string<CharType> toLower(const std::basic_string<CharType> &str) {
			std::basic_string<CharType> result(str.size(), ' ');
			std::transform(str.begin(), str.end(), result.begin(), tolower);
			return result;
		}
		
		/**
		 * Converts a string to upper case.
		 * @param str String to have its case upped.
		 * @return String in all upper case.
		 */
		template <typename CharType>
		static std::basic_string<CharType> toUpper(const std::basic_string<CharType> &str) {
			std::basic_string<CharType> result(str.size(), ' ');
			std::transform(str.begin(), str.end(), result.begin(), toupper);
			return result;
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
