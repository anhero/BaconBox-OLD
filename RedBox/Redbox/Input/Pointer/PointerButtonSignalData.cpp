#include "PointerButtonSignalData.h"

using namespace RedBox;

PointerButtonSignalData::PointerButtonSignalData(const PointerState& newPointerState,
												 unsigned int newCursorIndex,
												 CursorButton::Enum newCursorButton) :
PointerSignalData(newPointerState), cursorIndex(newCursorIndex),
cursorButton(newCursorButton) {
}
