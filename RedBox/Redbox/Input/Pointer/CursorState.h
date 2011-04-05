/**
 * @file
 * @ingroup Input
 */
#ifndef RB_CURSOR_STATE_H
#define RB_CURSOR_STATE_H

#include <vector>

#include "Vec2.h"

namespace RedBox {
	/**
	 * Represents the state of a cursor. Can be a mouse or a touch. In the case
	 * of a touch, there would be only one button. The number of buttons can
	 * be set to accomodate the pointing device.
	 * @ingroup Input
	 */
	struct CursorState {
		/**
		 * Default number of buttons a cursor has (simple mouse with a left
		 * button, a right button, a middle button and a scroll wheel).
		 */
		static const unsigned int DEFAULT_NB_BUTTONS = 5;
		
		/**
		 * Parameterized constructor.
		 * @param x Starting horizontal position.
		 * @param y Starting vertical position.
		 * @param nbButtons Number of buttons the cursor has.
		 */
		CursorState(unsigned int nbButtons = 5, float x = 0.0f, float y = 0.0f);
		
		/// Cursor's position.
		Vec2 position;
		
		/**
		 * State of current buttons, values set to true mean the button is
		 * pressed.
		 */
		std::vector<bool> buttons;
		
		/**
		 * Previous state of buttons, each time the current buttons are updated,
		 * they are first backed up in this member.
		 */
		std::vector<bool> previousButtons;
	};
}

#endif