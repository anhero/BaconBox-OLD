/**
 * @file
 * @ingroup Display
 */
#ifndef RB_COLORFORMAT_H
#define RB_COLORFORMAT_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {

	/**
	 * Enum type representing the color component format.
	 * Used internally to interpret buffers values.
	 * @ingroup Display
	 */
	struct ColorFormatDef {
		enum type {
			RGBA,
			ALPHA
		};
	};
	typedef SafeEnum<ColorFormatDef> ColorFormat;
}

#endif
