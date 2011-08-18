#ifndef RB_BUTTON_STATE_H
#define RB_BUTTON_STATE_H

#include "SafeEnum.h"

namespace RedBox {
	struct ButtonStateDef {
		enum type {
		    NORMAL,
		    HOVER,
		    PRESSED
		};
	};
	typedef SafeEnum<ButtonStateDef> ButtonState;
}

#endif
