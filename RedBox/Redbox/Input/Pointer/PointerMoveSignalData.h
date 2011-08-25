/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_MOVE_SIGNAL_DATA_H
#define RB_POINTER_MOVE_SIGNAL_DATA_H

#include "PointerSignalData.h"

namespace RedBox {
	/**
	 * Contains data about a signal sent when a pointing device does a button
	 * up or a button down.
	 * @ingroup Input
	 */
	class PointerMoveSignalData : public PointerSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newPointerState State of the pointer that sent the signal.
		 * @param newCursorIndex Index of the cursor that had a button changed.
		 */
		PointerMoveSignalData(const PointerState& newPointerState,
							  unsigned int newCursorIndex);
		
		/// Index of the cursor concerned by the signal.
		const unsigned int cursorIndex;
	};
}

#endif
