#include "BaconBox/Input/GamePad/GamePadState.h"
using namespace BaconBox;

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


void GamePadState::init(unsigned int nbOfButtons, unsigned int nbOfThumbstick){
    buttons = std::vector<float>(nbOfButtons, 0.0f);
    previousButtons = std::vector<float>(nbOfButtons, 0.0f);
    thumbsticks = std::vector<float>(nbOfThumbstick, 0.0f);
    previousThumbsticks = std::vector<float>(nbOfThumbstick, 0.0f);
}

const float GamePadState::getThumbstick(unsigned int thumbstickIndex) const {
	if(thumbstickIndex >= thumbsticks.size()) {
		thumbstickIndex = thumbsticks.size() - 1;
	}
	return thumbsticks[thumbstickIndex];
}




bool GamePadState::isButtonPressed(unsigned int buttonIndex) const {
	return (buttons[buttonIndex] && !previousButtons[buttonIndex]);
}

bool GamePadState::isButtonHeld(unsigned int buttonIndex) const {
	return (buttons[buttonIndex] && previousButtons[buttonIndex]);
}

bool GamePadState::isButtonReleased(unsigned int buttonIndex) const {
	return (!buttons[buttonIndex] && previousButtons[buttonIndex]);
}
