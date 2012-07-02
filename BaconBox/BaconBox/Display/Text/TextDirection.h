/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_TEXT_DIRECTION_H
#define RB_TEXT_DIRECTION_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {
	struct TextDirectionDef {
		enum type {
			LEFT_TO_RIGHT,
			RIGHT_TO_LEFT
			// TODO: UP_TO_DOWN
		};
	};
	/**
	 * Text direction, usually from left to right, but can be from right to left
	 * for some languages.
	 * @ingroup TextDisplay
	 */
	typedef SafeEnum<TextDirectionDef> TextDirection;
}

#endif
