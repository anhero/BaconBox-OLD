#include "PointerSignalData.h"

using namespace RedBox;

PointerSignalData::PointerSignalData(const PointerState& newPointerState,
                                     unsigned int newCursorIndex) :
	InputSignalData(), pointerState(newPointerState), cursorIndex(newCursorIndex) {
}

PointerSignalData::~PointerSignalData() {
}


const Vector2& PointerSignalData::getPosition() const {
	return pointerState.getCursorState(cursorIndex).getPosition();
}


float PointerSignalData::getXPosition() const {
	return getPosition().getX();
}

float PointerSignalData::getYPosition() const {
	return getPosition().getY();
}

const Vector2& PointerSignalData::getPreviousPosition() const {
	return pointerState.getCursorState().getPreviousPosition();
}


float PointerSignalData::getPreviousXPosition() const {
	return getPreviousPosition().getX();
}

float PointerSignalData::getPreviousYPosition() const {
	return getPreviousPosition().getY();
}
