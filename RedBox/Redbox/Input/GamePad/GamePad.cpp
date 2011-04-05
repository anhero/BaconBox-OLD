#include "GamePad.h"

using namespace RedBox;

const GamePadState& GamePad::getState() const {
	return state;
}

GamePad::GamePad() : InputDevice() {
}

GamePad::~GamePad() {
}

