/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_TEXT_ALIGNMENT_H
#define RB_TEXT_ALIGNMENT_H

#include "SafeEnum.h"

namespace RedBox {
	/**
	 * Different text alignments used for graphic strings.
	 */
	struct TextAlignmentDef {
		enum type {
			LEFT,
			RIGHT,
			CENTER
		};
	};
	typedef SafeEnum<TextAlignmentDef> TextAlignment;
}

#endif
