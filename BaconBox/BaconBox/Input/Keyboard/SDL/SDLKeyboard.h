#ifndef RB_SDL_KEYBOARD_H
#define RB_SDL_KEYBOARD_H

#include "BaconBox/PlatformFlagger.h"

#ifdef RB_SDL

#include <vector>

#include "BaconBox/Input/Keyboard/Keyboard.h"
#include "BaconBox/Input/Keyboard/Key.h"

namespace BaconBox {
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
		/// Mappings for SDL's key codes with BaconBox's key codes.
		std::vector<Key::Enum> mappings;
		/**
		 * Fills the key code mappings.
		 */
		void fillMappings();
	};
}

#endif

#endif
