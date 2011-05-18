#include "KeySignalData.h"

using namespace RedBox;

KeySignalData::KeySignalData(const KeyboardState& newKeyboardState,
							 Key::Enum newKey):
KeyboardSignalData(newKeyboardState), key(newKey), keyChar(Key::toChar(newKey)) {
}

KeySignalData::~KeySignalData() {
}