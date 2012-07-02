/**
 * @file
 * @ingroup Input
 */
#ifndef RB_SDL_INPUT_MANAGER_H
#define RB_SDL_INPUT_MANAGER_H

#include "BaconBox/PlatformFlagger.h"

#ifdef RB_SDL

#include "BaconBox/Input/InputManager.h"

namespace BaconBox {
	class SDLInputManager : public InputManager {
		friend class InputManager;
	public:
		static SDLInputManager* getSDLInstance();
		bool isRunning() const;
	protected:
		SDLInputManager();
		~SDLInputManager();
		void update();
	private:
		static SDLInputManager* sdlInstance;
		bool running;
	};
}

#endif
#endif
