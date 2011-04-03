#include "PointerState.h"

#include "Debug.h"

using namespace RedBox;

PointerState::PointerState(unsigned int nbCursors, unsigned int nbButtons):
	InputState(), cursors(std::vector<CursorState>(nbCursors, CursorState(nbButtons))) {
}

PointerState::~PointerState() {
}

const CursorState& PointerState::getCursorState(unsigned int index) const {
	// If we go out of bound, we write an error message and we return the last
	// cursor state.
	if(index >= cursors.size()) {
		index = cursors.size() - 1;
		$ECHO("Tried to get a cursor's state that does not exist, returning instead the cursor state with the highest index.");
	}

	return cursors[index];
}
