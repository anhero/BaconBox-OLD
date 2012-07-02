#include "BaconBox/Input/Keyboard/KeyboardSignalData.h"

using namespace BaconBox;

KeyboardSignalData::KeyboardSignalData(const KeyboardState& newKeyboardState):
InputSignalData(), keyboardState(newKeyboardState) {
}

KeyboardSignalData::~KeyboardSignalData() {
}
