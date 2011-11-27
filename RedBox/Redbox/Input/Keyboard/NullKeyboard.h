/**
 * @file
 */
#ifndef RB_NULL_KEYBOARD_H
#define RB_NULL_KEYBOARD_H

#include "Keyboard.h"

namespace RedBox {
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
