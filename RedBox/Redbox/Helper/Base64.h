/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_BASE_64_H
#define RB_BASE_64_H

#include <string>

namespace RedBox {
	/**
	 * This class contains functions to encode and decode base 64 data.
	 * The code in these functions is based on René Nyffenegger's work
	 * (rene.nyffenegger@adp-gmbh.ch) at
	 * http://www.adp-gmbh.ch/cpp/common/base64.html
	 * Big thanks to him.
	 * @ingroup Helper.
	 */
	class Base64 {
	public:
		/**
		 * Decodes data from base 64.
		 * @param data String containing the data to decode.
		 * @param result String that will contain the decoded data.
		 * @return True if the encoding succeeded, false if not.
		 */
		bool decode(const std::string &data, std::string &result);

		/**
		 * Encodes the data to base 64.
		 * @param data String containing the data to encode.
		 * @param result String that will contain the encoded data.
		 * @return True if the encoding succeded, false if not.
		 */
		bool encode(const std::string &data, std::string &result);
	private:
		Base64();
		Base64(const Base64 &src);
	};
}

#endif
