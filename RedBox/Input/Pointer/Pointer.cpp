#include "Pointer.h"

using namespace RedBox;

const PointerState& Pointer::getState() const {
	return state;
}

Pointer::Pointer(unsigned int nbCursors, unsigned int nbButtons) :
	InputDevice(), state(PointerState(nbCursors, nbButtons)) {
}

Pointer::~Pointer() {
}
