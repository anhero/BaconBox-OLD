/**
 * @file
 * @ingroup Input
 */
#ifndef RB_SDL_POINTER_H
#define RB_SDL_POINTER_H

#include "Pointer.h"

namespace RedBox {
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
