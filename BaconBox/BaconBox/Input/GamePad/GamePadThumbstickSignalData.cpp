#include "BaconBox/Input/GamePad/GamePadThumbstickSignalData.h"

using namespace BaconBox;

GamePadThumbstickSignalData::GamePadThumbstickSignalData(const GamePadState& newGamePadState,
														 unsigned int newThumbstickIndex, unsigned gamePadIndex):
GamePadSignalData(newGamePadState, gamePadIndex), thumbstickIndex(newThumbstickIndex) {
}

GamePadThumbstickSignalData::~GamePadThumbstickSignalData() {
}
