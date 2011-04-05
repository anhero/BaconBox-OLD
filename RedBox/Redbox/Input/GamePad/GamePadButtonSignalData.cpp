#include "GamePadButtonSignalData.h"

using namespace RedBox;

GamePadButtonSignalData::GamePadButtonSignalData(const GamePadState& newGamePadState,
												 unsigned int newButtonIndex):
GamePadSignalData(newGamePadState), buttonIndex(newButtonIndex) {
}

GamePadButtonSignalData::~GamePadButtonSignalData() {
}
