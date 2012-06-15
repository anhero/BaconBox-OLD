#include "GamePad.h"

#include "InputManager.h"

using namespace RedBox;

GamePad* GamePad::getDefault() {
	return InputManager::getDefaultGamePad();
}

const GamePadState& GamePad::getState() const {
	return state;
}

GamePad::GamePad(int index) : InputDevice() {
    gamePadIndex = index;   
}

GamePad::~GamePad() {
}

void GamePad::updateDevice() {
	InputDevice::updateDevice();
}


unsigned int GamePad::getIndex(){
    return gamePadIndex;
}



std::vector<float>& GamePad::getPreviousButtons(){
    return state.previousButtons;
}

std::vector<float>& GamePad::getButtons(){
    return state.buttons;
}

std::vector<float>& GamePad::getThumbstick(){
    return state.thumbsticks;
}

std::vector<float>& GamePad::getPreviousThumbstick(){
    return state.previousThumbsticks;
}



bool GamePad::isButtonPressed(unsigned int buttonIndex) const {
    return state.isButtonPressed(buttonIndex);
}

bool GamePad::isButtonHeld(unsigned int buttonIndex) const {
	return state.isButtonHeld(buttonIndex);
}

bool GamePad::isButtonReleased(unsigned int buttonIndex) const {
	return state.isButtonReleased(buttonIndex);
}