#include "BaconBox/Input/Pointer/PointerState.h"

#include "BaconBox/Input/Pointer/CursorButton.h"

#include "BaconBox/Console.h"

using namespace BaconBox;

PointerState::PointerState(unsigned int nbCursors):
	InputState(), cursors(std::vector<CursorState>(nbCursors, CursorState())) {
}

PointerState::~PointerState() {
}

const CursorState& PointerState::getCursorState(unsigned int index) const {
	// If we go out of bound, we write an error message and we return the last
	// cursor state.
	if(index >= cursors.size()) {
		index = cursors.size() - 1;
		Console::println("Tried to get a cursor's state that does not exist, returning instead the cursor state with the highest index.");
	}

	return cursors[index];
}

Vector2& PointerState::getCursorPosition(unsigned int index) {
	return cursors[index].position;
}

Vector2& PointerState::getCursorPreviousPosition(unsigned int index) {
	return cursors[index].previousPosition;
}

std::vector<bool>& PointerState::getCursorButtons(unsigned int index) {
	return cursors[index].buttons;
}

std::vector<bool>& PointerState::getCursorPreviousButtons(unsigned int index) {
	return cursors[index].previousButtons;
}
