/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_COMPRESSION_H
#define RB_COMPRESSION_H

#include <vector>

#include "CompressionMethod.h"

namespace RedBox {
	/**
	 * Contains functions to decompress and compress data.
	 * @ingroup Helper
	 */
	class Compression {
	public:
		/// Vector of bytes.
		typedef std::vector<char> ByteVector;

		/**
		 * Decompresses either gzip or zlib data from a byte vector into another
		 * byte vector.
		 * @param data Data to decompress.
		 * @param result Uncompressed data goes into this byte vector. The size
		 * of the given byte vector is considered as the expected size.
		 * @return True on success, false otherwise. If the result byte vector
		 * is too small, the decompression fails.
		 */
		static bool decompress(const ByteVector &data, ByteVector &result);

		/**
		 * Compresses data from a byte vector into another byte vector.
		 * @param data Data to compress.
		 * @param compressionMethod Type of compression method to use, either
		 * gzip or zlib.
		 * @param result Compressed data goes into this byte vector.
		 * @return True on success, false otherwise.
		 */
		static bool compress(const ByteVector &data,
		                     CompressionMethod compressionMethod,
		                     ByteVector &result);
	private:
		Compression();
		Compression(const Compression &src);
	};
}
#endif
