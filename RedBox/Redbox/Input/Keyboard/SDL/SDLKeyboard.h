#ifndef RB_SDL_KEYBOARD_H
#define RB_SDL_KEYBOARD_H

#include "PlatformFlagger.h"

#ifdef RB_SDL

#include <vector>

#include "Keyboard.h"
#include "Key.h"

namespace RedBox {
	class SDLKeyboard : public Keyboard {
		friend class InputManager;
	protected:
		/**
		 * Constructor.
		 * @param Pointer to the parent widget.
		 */
		SDLKeyboard();
		/**
		 * Destructor.
		 */
		~SDLKeyboard();
		/**
		 * Updates the keyboard.
		 */
		void updateDevice();
	private:
		/// Mappings for SDL's key codes with RedBox's key codes.
		std::vector<Key::Enum> mappings;
		/**
		 * Fills the key code mappings.
		 */
		void fillMappings();
	};
}

#endif

#endif