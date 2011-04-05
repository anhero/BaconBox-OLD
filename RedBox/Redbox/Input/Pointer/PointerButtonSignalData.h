/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_BUTTON_SIGNAL_DATA_H
#define RB_POINTER_BUTTON_SIGNAL_DATA_H

#include "PointerSignalData.h"

namespace RedBox {
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
		 * @param newButtonIndex Index of the button that is concerned by the
		 * signal.
		 */
		PointerButtonSignalData(const PointerState& newPointerState,
								unsigned int newCursorIndex,
								unsigned int newButtonIndex);
		
		/**
		 * Destructor.
		 */
		~PointerButtonSignalData();
		
		/// Index of the cursor concerned by the signal.
		const unsigned int cursorIndex;
		
		/// Index of the button concerned by the button.
		const unsigned int buttonIndex;
	};
}

#endif