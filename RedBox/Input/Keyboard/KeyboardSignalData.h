/**
 * @file
 * @ingroup Input
 */
#ifndef RB_KEYBOARD_SIGNAL_DATA_H
#define RB_KEYBOARD_SIGNAL_DATA_H

#include "InputSignalData.h"
#include "KeyboardState.h"

namespace RedBox {
	/**
	 * Base class for all signal data sent by a keyboard.
	 * @ingroup Input
	 */
	class KeyboardSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newKeyboardState State of the keyboard that sent the signal.
		 */
		KeyboardSignalData(const KeyboardState& newKeyboardState);

		/**
		 * Destructor.
		 */
		virtual ~KeyboardSignalData();

		/// State of the keyboard that sent the signal.
		const KeyboardState& keyboardState;
	};
}

#endif