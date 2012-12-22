#include "BaconBox/Input/Pointer/SDL/SDLPointer.h"

#include <stdint.h>

#include <SDL2/SDL.h>

using namespace BaconBox;

SDLPointer::SDLPointer() : Pointer() {
}

SDLPointer::~SDLPointer() {
}

void SDLPointer::updateDevice() {
	getCursorPreviousButtons(0) = getCursorButtons(0);
	getCursorPreviousPosition(0) = getCursorPosition(0);
	int x, y; // For the mouse position.
	// We check the pointer's buttons' states.
	Uint8 buttons = SDL_GetMouseState(&x, &y);
	getCursorPosition(0) = Vector2(static_cast<float>(x), static_cast<float>(y));
	getCursorButtons(0)[CursorButton::LEFT] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_LEFT));
	getCursorButtons(0)[CursorButton::RIGHT] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_RIGHT));
	getCursorButtons(0)[CursorButton::MIDDLE] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	getCursorButtons(0)[CursorButton::OTHER_BUTTON_1] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_X1));
	getCursorButtons(0)[CursorButton::OTHER_BUTTON_2] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_X2));
	//getCursorButtons(0)[CursorButton::SCROLL_UP] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_WHEELUP));
	//getCursorButtons(0)[CursorButton::SCROLL_DOWN] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_WHEELDOWN));
	for(CursorButton::Enum i = 0; i < CursorButton::NB_BUTTONS; ++i) {
		if(isButtonPressed(i)) {
			buttonPress(PointerButtonSignalData(state, 0, i));
		} else if(isButtonHeld(i)) {
			buttonHold(PointerButtonSignalData(state, 0, i));
		} else if(isButtonReleased(i)) {
			buttonRelease(PointerButtonSignalData(state, 0, i));
		}
	}

	// We check the pointer's position.
	if(hasMoved()) {
		Pointer::move.shoot(PointerSignalData(state, 0));
	}
}
