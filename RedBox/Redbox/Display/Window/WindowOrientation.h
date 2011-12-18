#ifndef RB_WINDOW_ORIENTATION
#define RB_WINDOW_ORIENTATION

#include "SafeEnum.h"

namespace RedBox {
	struct WindowOrientationDef {
		enum type {
			NORMAL,
			UPSIDE_DOWN,
			HORIZONTAL_LEFT,
			HORIZONTAL_RIGHT
		};
	};
	
	typedef SafeEnum<WindowOrientationDef> WindowOrientation;
}

#endif