/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_COMPRESSION_METHOD_H
#define RB_COMPRESSION_METHOD_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {
	/**
	 * Represents the different compression methods.
	 */
	struct CompressionMethodDef {
		enum type {
		    GZIP,
		    ZLIB
		};
	};
	typedef SafeEnum<CompressionMethodDef> CompressionMethod;
}
#endif
