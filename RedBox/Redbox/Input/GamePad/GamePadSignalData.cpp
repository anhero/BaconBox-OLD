#include "GamePadSignalData.h"

using namespace RedBox;

GamePadSignalData::GamePadSignalData(const GamePadState& newGamePadState, unsigned int gamePadIndex):
InputSignalData(), gamePadState(newGamePadState), gamePadIndex(gamePadIndex) {
}

GamePadSignalData::~GamePadSignalData() {
}
