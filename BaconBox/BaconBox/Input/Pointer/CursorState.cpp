#include "BaconBox/Input/Pointer/CursorState.h"

using namespace BaconBox;

CursorState::CursorState(float x, float y): position(Vector2(x, y)),
previousPosition(Vector2(x, y)),
buttons(std::vector<bool>(CursorButton::NB_BUTTONS, false)),
previousButtons(std::vector<bool>(CursorButton::NB_BUTTONS, false)) {
}

const Vector2& CursorState::getPosition() const {
	return position;
}

const Vector2& CursorState::getPreviousPosition() const {
	return previousPosition;
}

bool CursorState::hasMoved() const {
	return position != previousPosition;
}

bool CursorState::isButtonPressed(CursorButton::Enum button) const {
	return (button == CursorButton::INVALID) ? (false) : (buttons[button] && !previousButtons[button]);
}

bool CursorState::isButtonHeld(CursorButton::Enum button) const {
	return (button == CursorButton::INVALID) ? (false) : (buttons[button] && previousButtons[button]);
}

bool CursorState::isButtonReleased(CursorButton::Enum button) const {
	return (button == CursorButton::INVALID) ? (false) : (!buttons[button] && previousButtons[button]);
}
