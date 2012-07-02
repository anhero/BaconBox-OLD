#include "BaconBox/Input/Pointer/Pointer.h"

#include "BaconBox/Input/InputManager.h"

using namespace BaconBox;

Pointer* Pointer::getDefault() {
	return InputManager::getDefaultPointer();
}

const Vector2& Pointer::getPosition(unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].getPosition();
}

const Vector2& Pointer::getPreviousPosition(unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].getPreviousPosition();
}

bool Pointer::hasMoved(unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].hasMoved();
}

bool Pointer::isButtonPressed(CursorButton::Enum button, unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].isButtonPressed(button);
}

bool Pointer::isButtonHeld(CursorButton::Enum button, unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].isButtonHeld(button);
}

bool Pointer::isButtonReleased(CursorButton::Enum button, unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].isButtonReleased(button);
}

const PointerState& Pointer::getState() const {
	return state;
}

Pointer::Pointer(unsigned int nbCursors) : InputDevice(), state(PointerState(nbCursors)) {
}

Pointer::~Pointer() {
}

void Pointer::updateDevice() {
	InputDevice::updateDevice();
}

std::vector<CursorState>& Pointer::getCursorStates() {
	return state.cursors;
}

Vector2& Pointer::getCursorPosition(unsigned int index) {
	return state.getCursorPosition(index);
}

Vector2& Pointer::getCursorPreviousPosition(unsigned int index) {
	return state.getCursorPreviousPosition(index);
}

std::vector<bool>& Pointer::getCursorButtons(unsigned int index) {
	return state.getCursorButtons(index);
}

std::vector<bool>& Pointer::getCursorPreviousButtons(unsigned int index) {
	return state.getCursorPreviousButtons(index);
}
