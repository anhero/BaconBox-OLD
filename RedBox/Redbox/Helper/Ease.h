/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_EASE_H
#define RB_EASE_H

#include "SafeEnum.h"

namespace RedBox {
	struct EaseDef {
		enum type {
			LINEAR,
			IN_QUADRATIC,
			OUT_QUADRATIC,
			IN_OUT_QUADRATIC,
			IN_CUBIC,
			OUT_CUBIC,
			IN_OUT_CUBIC,
			IN_QUARTIC,
			OUT_QUARTIC,
			IN_OUT_QUARTIC,
			IN_QUINTIC,
			OUT_QUINTIC,
			IN_OUT_QUINTIC,
			IN_SINE,
			OUT_SINE,
			IN_OUT_SINE,
			IN_EXPO,
			OUT_EXPO,
			IN_OUT_EXPO,
			IN_CIRCULAR,
			OUT_CIRCULAR,
			IN_OUT_CIRCULAR,
			IN_BOUNCE,
			OUT_BOUNCE,
			IN_OUT_BOUNCE
		};
	};
	/**
	 * Represents the different types of ease for tweening.
	 * @ingroup Helper
	 */
	typedef SafeEnum<EaseDef> Ease;
}

#endif
