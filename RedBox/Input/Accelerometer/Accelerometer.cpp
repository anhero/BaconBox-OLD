#include "Accelerometer.h"

using namespace RedBox;

void Accelerometer::activateSignals() {
	signalsActive = true;
}

void Accelerometer::deactivateSignals() {
	signalsActive = false;
}

bool Accelerometer::areSignalsActive() const {
	return signalsActive;
}

void Accelerometer::activate() {
	active = true;
}

void Accelerometer::deactivate() {
	active = false;
}

bool Accelerometer::isActive() const {
	return active;
}

Accelerometer::Accelerometer() : InputDevice() {
}

Accelerometer::~Accelerometer() {
}
