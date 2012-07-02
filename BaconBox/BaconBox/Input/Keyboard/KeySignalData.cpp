#include "BaconBox/Input/Keyboard/KeySignalData.h"

using namespace BaconBox;

KeySignalData::KeySignalData(const KeyboardState& newKeyboardState,
							 Key::Enum newKey):
KeyboardSignalData(newKeyboardState), key(newKey), keyChar(Key::toChar(newKey)) {
}

KeySignalData::~KeySignalData() {
}
