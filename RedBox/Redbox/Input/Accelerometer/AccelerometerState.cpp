#include "AccelerometerState.h"

using namespace RedBox;

const float AccelerometerState::STARTING_ACCELERATION = 0.0f;

AccelerometerState::AccelerometerState() : InputState(),
xAcceleration(STARTING_ACCELERATION), yAcceleration(STARTING_ACCELERATION),
zAcceleration(STARTING_ACCELERATION) {
}

AccelerometerState::~AccelerometerState() {
}

float AccelerometerState::getXAcceleration() const {
	return xAcceleration;
}

float AccelerometerState::getYAcceleration() const {
	return yAcceleration;
}

float AccelerometerState::getZAcceleration() const {
	return zAcceleration;
}
