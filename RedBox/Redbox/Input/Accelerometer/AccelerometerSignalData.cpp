#include "AccelerometerSignalData.h"

using namespace RedBox;

AccelerometerSignalData::AccelerometerSignalData(const AccelerometerState& newAccelerometerState) :
InputSignalData(), accelerometerState(newAccelerometerState) {
}

AccelerometerSignalData::~AccelerometerSignalData() {
}
