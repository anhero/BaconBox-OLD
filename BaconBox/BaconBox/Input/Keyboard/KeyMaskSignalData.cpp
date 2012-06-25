#include "KeyMaskSignalData.h"

using namespace BaconBox;

KeyMaskSignalData::KeyMaskSignalData(const KeyboardState& newKeyboardState,
									 const std::string& newMaskName):
KeyboardSignalData(newKeyboardState), maskName(newMaskName) {
}

KeyMaskSignalData::~KeyMaskSignalData() {
}
