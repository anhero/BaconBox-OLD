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
		 */
		PointerSignalData(const PointerState& newPointerState);
		
		/**
		 * Destructor.
		 */
		virtual ~PointerSignalData();
		
		/**
		 * Gets a vector of the pointer's position.
		 * @return 2D vector of the pointer's position.
		 */
		const Vec2& getPosition() const;
		
		/**
		 * Gets the pointer's horizontal position.
		 * @return Pointer's horizontal position.
		 */
		float getXPosition() const;
		
		/**
		 * Gets the pointer's vertical position.
		 * @return Pointer's vertical position.
		 */
		float getYPosition() const;
		
		/// State of the pointing device that sent the signal.
		const PointerState& pointerState;
	};
}

#endif
