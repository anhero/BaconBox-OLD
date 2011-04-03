#include "PointerSignalData.h"

using namespace RedBox;

PointerSignalData::PointerSignalData(const PointerState& newPointerState) : 
InputSignalData(), pointerState(newPointerState) {
}

PointerSignalData::~PointerSignalData() {
}
