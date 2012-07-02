#include "BaconBox/Input/Pointer/PointerSignalData.h"

using namespace BaconBox;

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
	return getPosition().x;
}

float PointerSignalData::getYPosition() const {
	return getPosition().y;
}

const Vector2& PointerSignalData::getPreviousPosition() const {
	return pointerState.getCursorState().getPreviousPosition();
}


float PointerSignalData::getPreviousXPosition() const {
	return getPreviousPosition().x;
}

float PointerSignalData::getPreviousYPosition() const {
	return getPreviousPosition().y;
}
