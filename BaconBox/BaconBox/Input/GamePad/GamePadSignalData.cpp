#include "BaconBox/Input/GamePad/GamePadSignalData.h"

using namespace BaconBox;

GamePadSignalData::GamePadSignalData(const GamePadState& newGamePadState, unsigned int gamePadIndex):
InputSignalData(), gamePadState(newGamePadState), gamePadIndex(gamePadIndex) {
}

GamePadSignalData::~GamePadSignalData() {
}
