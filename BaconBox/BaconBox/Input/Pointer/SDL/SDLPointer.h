/**
 * @file
 * @ingroup Input
 */
#ifndef RB_SDL_POINTER_H
#define RB_SDL_POINTER_H

#include "BaconBox/Input/Pointer/Pointer.h"

namespace BaconBox {
	/**
	 * Pointer implementation for SDL.
	 * @ingroup Input
	 */
	class SDLPointer : public Pointer {
		friend class InputManager;
	protected:
		/**
		 * Default constructor.
		 */
		SDLPointer();
		
		/**
		 * Destructor.
		 */
		~SDLPointer();
		
		/**
		 * Updates the mouse's buttons state from SDL's mouse state.
		 */
		void updateDevice();
	};
}

#endif
