#include "BaconBox/Input/Accelerometer/AccelerometerState.h"

using namespace BaconBox;

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
