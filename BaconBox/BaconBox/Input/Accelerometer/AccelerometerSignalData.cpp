#include "BaconBox/Input/Accelerometer/AccelerometerSignalData.h"

using namespace BaconBox;

AccelerometerSignalData::AccelerometerSignalData(const AccelerometerState& newAccelerometerState) :
InputSignalData(), accelerometerState(newAccelerometerState) {
}

AccelerometerSignalData::~AccelerometerSignalData() {
}
