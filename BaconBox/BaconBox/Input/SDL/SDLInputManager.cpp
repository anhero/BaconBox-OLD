#include "PlatformFlagger.h"

#ifdef RB_SDL

#include "SDLInputManager.h"

#include <SDL/SDL.h>

using namespace BaconBox;

SDLInputManager* SDLInputManager::sdlInstance = NULL;

SDLInputManager* SDLInputManager::getSDLInstance() {
	return sdlInstance;
}

bool SDLInputManager::isRunning() const {
	return running;
}

SDLInputManager::SDLInputManager() : InputManager(), running(true) {
	sdlInstance = this;
}

SDLInputManager::~SDLInputManager() {
}

void SDLInputManager::update() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
	}
	InputManager::update();
}

#endif