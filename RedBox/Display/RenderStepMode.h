/**
 * @file
 * @ingroup Display
 */

#ifndef __RENDER_STEP_MODE_H
#define __RENDER_STEP_MODE_H

namespace RedBox {
	namespace RenderStepMode {
		typedef unsigned int Enum;
		const RenderStepMode SHAPE = 1;
		const RenderStepMode TEXTURE = 2;
		const RenderStepMode COLOR = 4;
	}
}
#endif