/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDER_STEP_MODE_H
#define RB_RENDER_STEP_MODE_H

#include "SafeEnum.h"

namespace RedBox {

	struct RenderModeDef {
		enum type {
			SHAPE,
			TEXTURE,
			COLOR,
			MASKED,
			INVERSE_MASKED
		};
	};
	typedef SafeEnum<RenderModeDef> RenderMode;
}
#endif
