/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_SIGNAL_DATA_H
#define RB_POINTER_SIGNAL_DATA_H

#include "BaconBox/Input/InputSignalData.h"
#include "BaconBox/Input/Pointer/PointerState.h"

namespace BaconBox {
	/**
	 * Base class for all signal data sent by a pointing device.
	 * @ingroup Input
	 */
	class PointerSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newPointerState State of the pointer that sent the signal.
		 * @param newCursorIndex Index of the cursor that had a button changed.
		 */
		PointerSignalData(const PointerState& newPointerState,
		                  unsigned int newCursorIndex);

		/**
		 * Destructor.
		 */
		virtual ~PointerSignalData();

		/**
		 * Gets a vector of the pointer's position.
		 * @return 2D vector of the pointer's position.
		 */
		const Vector2& getPosition() const;

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

		/**
		 * Gets a vector of the pointer's previous position.
		 * @return 2D vector of the pointer's previous position.
		 */
		const Vector2& getPreviousPosition() const;

		/**
		 * Gets the pointer's horizontal previous position.
		 * @return Pointer's horizontal previous position.
		 */
		float getPreviousXPosition() const;

		/**
		 * Gets the pointer's vertical previous position.
		 * @return Pointer's vertical previous position.
		 */
		float getPreviousYPosition() const;

		/// State of the pointing device that sent the signal.
		const PointerState& pointerState;

		/// Index of the cursor concerned by the signal.
		const unsigned int cursorIndex;
	};
}

#endif
