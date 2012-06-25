/**
 * @file
 * @ingroup Helper
 */

#ifndef RB_PARSER_H
#define RB_PARSER_H

#define RB_FULL_PRECISION -1

#include <string>


namespace BaconBox {
	/**
	 * This helper class is used to parse number to/from string 
	 * @ingroup Helper
	 */
	class Parser {
	public:
		/**
		 * Parse the given string to an integer Ex: "123" would give 123.
		 */
		static int stringToInt(const std::string& str);
		
		/**
		 * Create a string from the given integer. Ex: 123 would give "123".
		 */
		static std::string intToString(const int anInt);
		
		/**
		 * Create a string from the given float. Ex: 12.3 would give "12.3".
		 */
		static std::string doubleToString(const double aFloat, int precision = RB_FULL_PRECISION);
	};
}

#endif
