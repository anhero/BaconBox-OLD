#include "Pointer.h"

#include "InputManager.h"

using namespace RedBox;

Pointer* Pointer::getDefault() {
	return InputManager::getDefaultPointer();
}

const Vec2& Pointer::getPosition(unsigned int cursorIndex) const {
	return state.cursors[cursorIndex].getPosition();
}

const Vec2& Pointer::getPreviousPosition(unsigned int cursorIndex) const {
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

Vec2& Pointer::getCursorPosition(unsigned int index) {
	return state.getCursorPosition(index);
}

Vec2& Pointer::getCursorPreviousPosition(unsigned int index) {
	return state.getCursorPreviousPosition(index);
}

std::vector<bool>& Pointer::getCursorButtons(unsigned int index) {
	return state.getCursorButtons(index);
}

std::vector<bool>& Pointer::getCursorPreviousButtons(unsigned int index) {
	return state.getCursorPreviousButtons(index);
}
