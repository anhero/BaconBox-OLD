#include "Accelerometer.h"

using namespace RedBox;

double Accelerometer::xAccelValue = 0;
double Accelerometer::yAccelValue = 0;
double Accelerometer::zAccelValue = 0;


double Accelerometer::getXAccelValue(){
	return xAccelValue;
}

double Accelerometer::getYAccelValue(){
	return yAccelValue;
}

double Accelerometer::getZAccelValue(){
	return zAccelValue;
}

void Accelerometer::setAccelValue(double x, double y, double z){
	xAccelValue = x;
	yAccelValue = y;
	zAccelValue = z;
}

void Accelerometer::setupAccelerometer(int updatesPerSecond){
#ifdef RB_IPHONE_PLATFORM
	UIAccelerometer*  theAccelerometer = [UIAccelerometer sharedAccelerometer];
	theAccelerometer.updateInterval = 1.0 / updatesPerSecond;
    theAccelerometer.delegate = [RBAccelerometerDelegate getAccelDelegate];
#endif

}
