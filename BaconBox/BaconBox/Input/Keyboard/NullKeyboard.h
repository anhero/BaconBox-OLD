/**
 * @file
 * @ingroup Input
 */
#ifndef RB_NULL_KEYBOARD_H
#define RB_NULL_KEYBOARD_H

#include "BaconBox/Input/Keyboard/Keyboard.h"

namespace BaconBox {
	/**
	 * Null keyboard device. Used when the platform doesn't have a keyboard.
	 * @ingroup Input
	 */
	class NullKeyboard : public Keyboard {
	public:
		/**
		 * Default constructor.
		 */
		NullKeyboard();

		/**
		 * Destructor.
		 */
		~NullKeyboard();

		/**
		 * Updates the keyboard device. It actually does not do anything.
		 */
		void updateDevice();
	};

}

#endif // RB_NULL_KEYBOARD_H
