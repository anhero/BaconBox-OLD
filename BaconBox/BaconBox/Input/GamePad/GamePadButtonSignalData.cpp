#include "BaconBox/Input/GamePad/GamePadButtonSignalData.h"

using namespace BaconBox;

GamePadButtonSignalData::GamePadButtonSignalData(const GamePadState& newGamePadState,
												 unsigned int newButtonIndex, unsigned gamePadIndex):
GamePadSignalData(newGamePadState, gamePadIndex), buttonIndex(newButtonIndex) {
}

GamePadButtonSignalData::~GamePadButtonSignalData() {
}
