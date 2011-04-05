#include "GamePadSignalData.h"

using namespace RedBox;

GamePadSignalData::GamePadSignalData(const GamePadState& newGamePadState):
InputSignalData(), gamePadState(newGamePadState) {
}

GamePadSignalData::~GamePadSignalData() {
}
