#include "BaconBox/Helper/Compression.h"

#include <cassert>

#include <zlib.h>

#include "BaconBox/Console.h"

namespace BaconBox {
	const std::string::size_type DEFAULT_RESULT_SIZE = 1024;
	void logZlibError(int error);

	bool Compression::decompress(const std::string &data, std::string &result) {
		bool success = true;

		// We make sure there is data to decompress.
		if (!data.empty()) {
			// In case the result byte vector is empty, we give it a size.
			if (result.empty()) {
				result.resize(DEFAULT_RESULT_SIZE);
			}

			// We initialize the zlib stream.
			z_stream zStream;
			zStream.zalloc = Z_NULL;
			zStream.zfree = Z_NULL;
			zStream.opaque = Z_NULL;
			zStream.next_in = reinterpret_cast<Bytef *>(const_cast<std::string::pointer>(&data[0]));
			zStream.avail_in = static_cast<uInt>(data.size());
			zStream.next_out = reinterpret_cast<Bytef *>(&result[0]);
			zStream.avail_out = static_cast<uInt>(result.size());

			// We initialize the decompression.
			int ret = inflateInit2(&zStream, 15 + 32);

			// We need this variable in case the result byte vector is too
			// small.
			std::string::size_type oldSize;

			// We make sure the zlib stream is ok.
			if (ret == Z_OK) {
				// We decompress until it's all decompressed...
				do {
					ret = inflate(&zStream, Z_SYNC_FLUSH);

					// We make sure there aren't any errors.
					switch (ret) {
					case Z_NEED_DICT:
					case Z_STREAM_ERROR:
						ret = Z_DATA_ERROR;

					case Z_DATA_ERROR:
					case Z_MEM_ERROR:
						inflateEnd(&zStream);
						logZlibError(ret);
						success = false;
						break;

					default:
						break;
					}

					// If the result byte vector doesn't have enough room, we
					// resize it.
					if (success && ret != Z_STREAM_END) {
						oldSize = result.size();
						result.resize(result.size() * 2);

						zStream.next_out = reinterpret_cast<Bytef *>(&result[0] + oldSize);
						zStream.avail_out = static_cast<uInt>(oldSize);
					}

				} while (success && ret != Z_STREAM_END);

				// We make sure the decompression was successful.
				if (success && zStream.avail_in == 0) {
					// If the result byte vector is too big, we make it smaller
					// to fit with the decompressed data.
					const std::string::size_type outSize = result.size() - zStream.avail_out;
					inflateEnd(&zStream);

					result.resize(outSize);

				} else {
					logZlibError(Z_DATA_ERROR);
					success = false;
				}

			} else {
				success = false;
			}

		} else {
			success = false;
		}

		return success;
	}

	bool Compression::compress(const std::string &data,
	                           CompressionMethod compressionMethod,
	                           std::string &result) {
		bool success = true;

		if (!data.empty()) {
			result.resize(DEFAULT_RESULT_SIZE);
			int error;
			z_stream zStream;
			zStream.zalloc = Z_NULL;
			zStream.zfree = Z_NULL;
			zStream.opaque = Z_NULL;
			zStream.next_in = reinterpret_cast<Bytef *>(const_cast<std::string::pointer>(&data[0]));
			zStream.avail_in = data.size();
			zStream.next_out = reinterpret_cast<Bytef *>(&result[0]);
			zStream.avail_out = result.size();

			const int windowBits = (compressionMethod == CompressionMethod::GZIP) ? (31) : (15);

			error = deflateInit2(&zStream,
			                     Z_DEFAULT_COMPRESSION,
			                     Z_DEFLATED,
			                     windowBits,
			                     8,
			                     Z_DEFAULT_STRATEGY);
			std::string::size_type oldSize;

			if (error == Z_OK) {
				do {
					error = deflate(&zStream, Z_FINISH);

					assert(error != Z_STREAM_ERROR);

					if (error == Z_OK) {
						// We need more space in the result string.
						oldSize = result.size();
						result.resize(result.size() * 2);

						zStream.next_out = reinterpret_cast<Bytef *>(&result[0] + oldSize);
						zStream.avail_out = static_cast<uInt>(oldSize);
					}

				} while (error == Z_OK);

				if (error == Z_STREAM_END) {
					const std::string::size_type outSize = result.size() - zStream.avail_out;
					deflateEnd(&zStream);

					result.resize(outSize);

				} else {
					logZlibError(error);
					deflateEnd(&zStream);
					result.clear();
					success = false;
				}

			} else {
				logZlibError(error);
				result.clear();
				success = false;
			}
		}

		return success;
	}

	void logZlibError(int error) {
		switch (error) {
		case Z_MEM_ERROR:
			Console::println("Out of memory while (de)compressing data!");
			break;

		case Z_VERSION_ERROR:
			Console::println("Incompatible zlib version!");
			break;

		case Z_NEED_DICT:
		case Z_DATA_ERROR:
			Console::println("Incorrect zlib compressed data!");
			break;

		default:
			Console::println("Unknown error while (de)compressing data!");
			break;
		}
	}
}
