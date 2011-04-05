#include "KeyboardSignalData.h"

using namespace RedBox;

KeyboardSignalData::KeyboardSignalData(const KeyboardState& newKeyboardState):
InputSignalData(), keyboardState(newKeyboardState) {
}

KeyboardSignalData::~KeyboardSignalData() {
}
