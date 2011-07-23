/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDER_STEP_MODE_H
#define RB_RENDER_STEP_MODE_H

#include "SafeEnum.h"

namespace RedBox {

	struct RenderStepModeDef {
		enum type {
			SHAPE,
			TEXTURE,
			COLOR,
            MASKED
		};
	};
	typedef SafeEnum<RenderStepModeDef> RenderStepMode;
}
#endif
