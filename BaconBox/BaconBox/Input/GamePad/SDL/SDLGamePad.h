/**
 * @file
 */
#ifndef RB_GAMEPAD_H
#define RB_GAMEPAD_H

#include "BaconBox/Input/GamePad/GamePad.h"
#include <SDL2/SDL.h>

namespace BaconBox {
	/**
	 * 
	 */
	class SDLGamePad : GamePad {
        friend class InputManager;
	protected:
        
        
		SDLGamePad(int index);
		
		/**
		 * Destructor.
		 */
		~SDLGamePad();
		
		/**
		 * Abstract update method. This will be called to update the device's
		 * state.
		 */
		void updateDevice();
        
    
        
    private:
        SDL_Joystick *joystick;
        
        
        
        
        
	};
}

#endif // RB_GAMEPAD_H





