/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_H
#define RB_POINTER_H

#include <sigly.h>

#include "InputDevice.h"
#include "PointerButtonSignalData.h"
#include "PointerMoveSignalData.h"
#include "PointerState.h"

namespace RedBox {
	/**
	 * Represents a pointing device. A pointing device can have multiple
	 * pointers (like multiple mice or multiple touches) at the same time.
	 * When a device is physically disconnected, it does not get deleted in
	 * here, it would simply stop sending signals and would be set at its
	 * default state.
	 * @ingroup Input
	 */
	class Pointer : public InputDevice {
		friend class InputManager;
	public:
		/// Signal sent when a cursor button is pressed down.
		sigly::Signal1<PointerButtonSignalData> buttonPress;
		
		/// Signal sent when a cursor button is held.
		sigly::Signal1<PointerButtonSignalData> buttonHold;

		/// Signal sent when a cursor button is released.
		sigly::Signal1<PointerButtonSignalData> buttonRelease;

		/// Signal sent when a cursor has moved.
		sigly::Signal1<PointerMoveSignalData> move;
		
		/**
		 * Gets a pointer to the default pointer device.
		 * @return Pointer to the default pointer device. Null if none are
		 * available.
		 */
		static Pointer* getDefault();

		/**
		 * Gets the cursor's position.
		 * @param Index of the cursor to check.
		 * @return Cursor's position.
		 */
		const Vec2& getPosition(unsigned int cursorIndex = 0) const;

		/**
		 * Gets the cursor's previous position.
		 * @return Cursor's previous position.
		 */
		const Vec2& getPreviousPosition(unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the cursor has just moved.
		 * @return True if the cursor has just moved, false if not.
		 */
		bool hasMoved(unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the specified button was just pressed.
		 * @param button Button to check.
		 * @param Index of the cursor to check.
		 * @return True if the button was just pressed, false if not.
		 */
		bool isButtonPressed(CursorButton::Enum button, unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the specified button is being held down.
		 * @param button Button to check.
		 * @param Index of the cursor to check.
		 * @return True if the button is being held down, false if not.
		 */
		bool isButtonHeld(CursorButton::Enum button, unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the specified button was just released.
		 * @param button Button to check.
		 * @param Index of the cursor to check.
		 * @return True if the button was just released, false if not.
		 */
		bool isButtonReleased(CursorButton::Enum button, unsigned int cursorIndex = 0) const;

		/**
		 * Gets the state of the pointer.
		 * @return State of the pointing device and its cursors.
		 */
		const PointerState& getState() const;
	protected:
		/// State of the pointing device's cursors.
		PointerState state;
		
		/**
		 * Parameterized constructor.
		 * @param nbCursors Number of cursors the pointing device(s) can
		 * support.
		 */
		Pointer(unsigned int nbCursors = PointerState::DEFAULT_NB_CURSORS);
		
		/**
		 * Destructor
		 */
		virtual ~Pointer();

		/**
		 * Gets the cursors' state. Used for platform specific implementation
		 * so they can access the required information.
		 * @return Reference to the cursors' state.
		 */
		std::vector<CursorState>& getCursorStates();

		/**
		 * Gets a cursor's position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's position.
		 */
		Vec2& getCursorPosition(unsigned int index);

		/**
		 * Gets a cursor's previous position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous position.
		 */
		Vec2& getCursorPreviousPosition(unsigned int index);

		/**
		 * Gets a cursor's buttons.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's buttons.
		 */
		std::vector<bool>& getCursorButtons(unsigned int index);

		/**
		 * Gets a cursor's previous buttons.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous buttons.
		 */
		std::vector<bool>& getCursorPreviousButtons(unsigned int index);
	};
}

#endif
