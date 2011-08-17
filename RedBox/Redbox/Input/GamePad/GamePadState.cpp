#include "GamePadState.h"

using namespace RedBox;

GamePadState::GamePadState() : InputState() {
}

GamePadState::~GamePadState() {
}

float GamePadState::getButton(unsigned int buttonIndex) const {
	if(buttonIndex >= buttons.size()) {
		buttonIndex = buttons.size() - 1;
	}
	return buttons[buttonIndex];
}

float GamePadState::getPreviousButton(unsigned int buttonIndex) const {
	if(buttonIndex >= previousButtons.size()) {
		buttonIndex = previousButtons.size() - 1;
	}
	return previousButtons[buttonIndex];
}

const Vector2& GamePadState::getThumbstick(unsigned int thumbstickIndex) const {
	if(thumbstickIndex >= thumbsticks.size()) {
		thumbstickIndex = thumbsticks.size() - 1;
	}
	return thumbsticks[thumbstickIndex];
}
