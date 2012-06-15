#include "GamePadButtonSignalData.h"

using namespace RedBox;

GamePadButtonSignalData::GamePadButtonSignalData(const GamePadState& newGamePadState,
												 unsigned int newButtonIndex, unsigned gamePadIndex):
GamePadSignalData(newGamePadState, gamePadIndex), buttonIndex(newButtonIndex) {
}

GamePadButtonSignalData::~GamePadButtonSignalData() {
}
