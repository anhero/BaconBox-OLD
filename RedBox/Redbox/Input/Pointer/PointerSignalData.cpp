#include "PointerSignalData.h"

using namespace RedBox;

PointerSignalData::PointerSignalData(const PointerState& newPointerState) : 
InputSignalData(), pointerState(newPointerState) {
}

PointerSignalData::~PointerSignalData() {
}


const Vec2& PointerSignalData::getPosition() const {
	return pointerState.getCursorState().getPosition();
}


float PointerSignalData::getXPosition() const {
	return getPosition().getX();
}

float PointerSignalData::getYPosition() const {
	return getPosition().getY();
}
