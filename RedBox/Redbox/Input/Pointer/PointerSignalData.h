/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_SIGNAL_DATA_H
#define RB_POINTER_SIGNAL_DATA_H

#include "InputSignalData.h"
#include "PointerState.h"

namespace RedBox {
	/**
	 * Base class for all signal data sent by a pointing device.
	 * @ingroup Input
	 */
	class PointerSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newPointerState State of the pointer that sent the signal.
		 * @param newCursorIndex Index of the cursor that is concerned by the
		 * signal.
		 */
		PointerSignalData(const PointerState& newPointerState);
		
		/**
		 * Destructor.
		 */
		virtual ~PointerSignalData();
		
		/// State of the pointing device that sent the signal.
		const PointerState& pointerState;
	};
}

#endif