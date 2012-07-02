/**
 * @file
 * @ingroup Input
 */
#ifndef RB_CURSOR_STATE_H
#define RB_CURSOR_STATE_H

#include <vector>

#include "BaconBox/Vector2.h"

#include "BaconBox/Input/Pointer/CursorButton.h"

namespace BaconBox {
	/**
	 * Represents the state of a cursor. Can be a mouse or a touch. In the case
	 * of a touch, there would be only one button. The number of buttons can
	 * be set to accommodate the pointing device.
	 * @ingroup Input
	 */
	class CursorState {
		friend class PointerState;
	public:
		/**
		 * Parameterized constructor.
		 * @param x Starting horizontal position.
		 * @param y Starting vertical position.
		 */
		CursorState(float x = 0.0f, float y = 0.0f);

		/**
		 * Gets the cursor's position.
		 * @return Cursor's position.
		 */
		const Vector2& getPosition() const;

		/**
		 * Gets the cursor's previous position.
		 * @return Cursor's previous position.
		 */
		const Vector2& getPreviousPosition() const;

		/**
		 * Checks if the cursor has just moved.
		 * @return True if the cursor has just moved, false if not.
		 */
		bool hasMoved() const;

		/**
		 * Checks if the specified button was just pressed.
		 * @param button Button to check.
		 * @return True if the button was just pressed, false if not.
		 */
		bool isButtonPressed(CursorButton::Enum button) const;

		/**
		 * Checks if the specified button is being held down.
		 * @param button Button to check.
		 * @return True if the button is being held down, false if not.
		 */
		bool isButtonHeld(CursorButton::Enum button) const;

		/**
		 * Checks if the specified button was just released.
		 * @param button Button to check.
		 * @return True if the button was just released, false if not.
		 */
		bool isButtonReleased(CursorButton::Enum button) const;
	private:
		/// Cursor's position.
		Vector2 position;

		/// Cursor's previous position.
		Vector2 previousPosition;

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
