#include "PointerMoveSignalData.h"

using namespace RedBox;

PointerMoveSignalData::PointerMoveSignalData(const PointerState& newPointerState,
											 unsigned int newCursorIndex) : 
PointerSignalData(newPointerState), cursorIndex(newCursorIndex) {
}
