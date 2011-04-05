#include "GamePadThumbstickSignalData.h"

using namespace RedBox;

GamePadThumbstickSignalData::GamePadThumbstickSignalData(const GamePadState& newGamePadState,
														 unsigned int newThumbstickIndex):
GamePadSignalData(newGamePadState), thumbstickIndex(newThumbstickIndex) {
}

GamePadThumbstickSignalData::~GamePadThumbstickSignalData() {
}
