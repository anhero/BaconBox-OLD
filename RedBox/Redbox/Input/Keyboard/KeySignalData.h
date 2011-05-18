/**
 * @file
 * @ingroup Input
 */
#ifndef RB_KEY_SIGNAL_DATA_H
#define RB_KEY_SIGNAL_DATA_H

#include "KeyboardSignalData.h"
#include "Key.h"

namespace RedBox {
	/**
	 * Contains data about a signal sent by a keyboard device when a key is
	 * either pressed, released or held.
	 * @ingroup Input
	 */
	class KeySignalData : public KeyboardSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newKeyboardState State of the keyboard that sent the signal.
		 * @param newKey Key concerned that was pressed, released or held.
		 */
		KeySignalData(const KeyboardState& newKeyboardState,
					  Key::Enum newKey);
		
		/**
		 * Destructor.
		 */
		~KeySignalData();
		
		/// Key concerned by the signal.
		const Key::Enum key;
		
		/// Key char associated with the key.
		const char keyChar;
	};
}

#endif