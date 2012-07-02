/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_TEXT_ALIGNMENT_H
#define RB_TEXT_ALIGNMENT_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {
	struct TextAlignmentDef {
		enum type {
			LEFT,
			RIGHT,
			CENTER
		};
	};
	/**
	 * Different text alignments used for graphic strings.
	 * @ingroup TextDisplay
	 */
	typedef SafeEnum<TextAlignmentDef> TextAlignment;
}

#endif
