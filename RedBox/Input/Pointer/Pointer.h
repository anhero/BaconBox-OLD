/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_H
#define RB_POINTER_H

#include <sigly/sigly.h>

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
		sigly::Signal1<PointerButtonSignalData> down;
		
		/// Signal sent when a cursor button is released.
		sigly::Signal1<PointerButtonSignalData> up;
		
		/// Signal sent when a cursor has moved.
		sigly::Signal1<PointerMoveSignalData> move;
		
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
		 * @param nbCursors Number of cursors the pointing device has. In the
		 * case of a multi touch interface, the number of touches you can have
		 * at the same time.
		 * @param nbButtons Number of buttons each cursors have. Touch
		 * pointing devices only have one button.
		 */
		Pointer(unsigned int nbCursors = PointerState::DEFAULT_NB_CURSORS,
				unsigned int nbButtons = CursorState::DEFAULT_NB_BUTTONS);
		
		/**
		 * Destructor
		 */
		virtual ~Pointer();
	};
}

#endif