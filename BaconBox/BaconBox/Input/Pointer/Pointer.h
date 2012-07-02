/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_H
#define RB_POINTER_H

#include <sigly.h>

#include "BaconBox/Input/InputDevice.h"
#include "BaconBox/Input/Pointer/PointerButtonSignalData.h"
#include "BaconBox/Input/Pointer/PointerState.h"

namespace BaconBox {
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
		sigly::Signal1<PointerSignalData> move;

		/**
		 * Gets a pointer to the default pointer device.
		 * @return Pointer to the default pointer device. Null if none are
		 * available.
		 */
		static Pointer* getDefault();

		/**
		 * Connect a function callback to the buttonPress signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectButtonPress(desttype* pclass, void (desttype::*pmemfun)(PointerButtonSignalData)) {
			Pointer* pointer = getDefault();

			if(pointer) {
				pointer->buttonPress.connect(pclass, pmemfun);
			}
		}

		/**
		 * Connect a function callback to the buttonHold signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectButtonHold(desttype* pclass, void (desttype::*pmemfun)(PointerButtonSignalData)) {
			Pointer* pointer = getDefault();

			if(pointer) {
				pointer->buttonHold.connect(pclass, pmemfun);
			}
		}

		/**
		 * Connect a function callback to the buttonRelease signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectButtonRelease(desttype* pclass, void (desttype::*pmemfun)(PointerButtonSignalData)) {
			Pointer* pointer = getDefault();

			if(pointer) {
				pointer->buttonRelease.connect(pclass, pmemfun);
			}
		}

		/**
		 * Connect a function callback to the buttonPress signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectMove(desttype* pclass, void (desttype::*pmemfun)(PointerSignalData)) {
			Pointer* pointer = getDefault();

			if(pointer) {
				pointer->move.connect(pclass, pmemfun);
			}
		}

		/**
		 * Gets the cursor's position.
		 * @param cursorIndex Index of the cursor to check.
		 * @return Cursor's position.
		 */
		const Vector2& getPosition(unsigned int cursorIndex = 0) const;

		/**
		 * Gets the cursor's previous position.
		 * @return Cursor's previous position.
		 */
		const Vector2& getPreviousPosition(unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the cursor has just moved.
		 * @return True if the cursor has just moved, false if not.
		 */
		bool hasMoved(unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the specified button was just pressed.
		 * @param button Button to check.
		 * @param cursorIndex Index of the cursor to check.
		 * @return True if the button was just pressed, false if not.
		 */
		bool isButtonPressed(CursorButton::Enum button,
		                     unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the specified button is being held down.
		 * @param button Button to check.
		 * @param cursorIndex Index of the cursor to check.
		 * @return True if the button is being held down, false if not.
		 */
		bool isButtonHeld(CursorButton::Enum button, unsigned int cursorIndex = 0) const;

		/**
		 * Checks if the specified button was just released.
		 * @param button Button to check.
		 * @param cursorIndex Index of the cursor to check.
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
		 * Abstract update method. This will be called to update the device's
		 * state.
		 */
		virtual void updateDevice();

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
		Vector2& getCursorPosition(unsigned int index);

		/**
		 * Gets a cursor's previous position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous position.
		 */
		Vector2& getCursorPreviousPosition(unsigned int index);

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
