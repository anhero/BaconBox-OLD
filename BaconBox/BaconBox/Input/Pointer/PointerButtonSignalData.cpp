#include "BaconBox/Input/Pointer/PointerButtonSignalData.h"

using namespace BaconBox;

PointerButtonSignalData::PointerButtonSignalData(const PointerState& newPointerState,
                                                 unsigned int newCursorIndex,
                                                 CursorButton::Enum newCursorButton) :
	PointerSignalData(newPointerState, newCursorIndex), cursorButton(newCursorButton) {
}
