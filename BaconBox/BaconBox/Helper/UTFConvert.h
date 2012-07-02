/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_UTF_CONVERT_H
#define RB_UTF_CONVERT_H

#include <string>

#include "BaconBox/Display/RBString32.h"

namespace BaconBox {
	/**
	 * This class is used to encode/decode/transcode UTF8, 16 and 32
	 * @ingroup Helper
	 */
	class UTFConvert {
	public:
		/**
		 * Encode the given UTF32 string to a 8bit UTF8 one.
		 */
		static std::string encodeToUTF8(const String32 &utf32String);

		/**
		 * Decode the given 8bit UTF8 string to an UTF32 string.
		 */
		static String32 decodeUTF8(const std::string &utf8String);
	};
}

#endif
