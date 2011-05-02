#include "PointerSignalData.h"

using namespace RedBox;

PointerSignalData::PointerSignalData(const PointerState& newPointerState) : 
InputSignalData(), pointerState(newPointerState) {
}

PointerSignalData::~PointerSignalData() {
}


Vec2 PointerSignalData::getPosition(){
	return pointerState.getCursorState().getPosition();
}


float PointerSignalData::getXPosition(){
	return getPosition().getX();
}

float PointerSignalData::getYPosition(){
	return getPosition().getY();
}