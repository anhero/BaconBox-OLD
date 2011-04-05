#include "PointerButtonSignalData.h"

using namespace RedBox;

PointerButtonSignalData::PointerButtonSignalData(const PointerState& newPointerState,
												 unsigned int newCursorIndex,
												 unsigned int newButtonIndex) :
PointerSignalData(newPointerState), cursorIndex(newCursorIndex),
buttonIndex(newButtonIndex) {
}

PointerButtonSignalData::~PointerButtonSignalData() {
}
