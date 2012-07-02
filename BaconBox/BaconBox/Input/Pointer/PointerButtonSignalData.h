/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_BUTTON_SIGNAL_DATA_H
#define RB_POINTER_BUTTON_SIGNAL_DATA_H

#include "BaconBox/Input/Pointer/PointerSignalData.h"
#include "BaconBox/Input/Pointer/CursorButton.h"

namespace BaconBox {
	/**
	 * Contains data about a signal sent when a pointing device does a button
	 * up or a button down.
	 * @ingroup Input
	 */
	class PointerButtonSignalData : public PointerSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newPointerState State of the pointer that sent the signal.
		 * @param newCursorIndex Index of the cursor that had a button changed.
		 * @param newCursorButton Index of the button that is concerned by the
		 * signal.
		 */
		PointerButtonSignalData(const PointerState& newPointerState,
		                        unsigned int newCursorIndex,
		                        CursorButton::Enum newCursorButton);

		/// Index of the button concerned by the button.
		const CursorButton::Enum cursorButton;
	};
}

#endif
