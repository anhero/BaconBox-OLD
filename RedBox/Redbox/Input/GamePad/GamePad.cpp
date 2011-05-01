#include "GamePad.h"

#include "InputManager.h"

using namespace RedBox;

GamePad* GamePad::getDefault() {
	return InputManager::getDefaultGamePad();
}

const GamePadState& GamePad::getState() const {
	return state;
}

GamePad::GamePad() : InputDevice() {
}

GamePad::~GamePad() {
}

