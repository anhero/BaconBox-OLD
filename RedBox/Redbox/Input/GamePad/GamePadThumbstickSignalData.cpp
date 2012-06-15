#include "GamePadThumbstickSignalData.h"

using namespace RedBox;

GamePadThumbstickSignalData::GamePadThumbstickSignalData(const GamePadState& newGamePadState,
														 unsigned int newThumbstickIndex, unsigned gamePadIndex):
GamePadSignalData(newGamePadState, gamePadIndex), thumbstickIndex(newThumbstickIndex) {
}

GamePadThumbstickSignalData::~GamePadThumbstickSignalData() {
}
