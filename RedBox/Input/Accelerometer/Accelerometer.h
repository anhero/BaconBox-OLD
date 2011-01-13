#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

#import "RBAccelerometerDelegate.h"

namespace RedBox {
	class Accelerometer{
	private:
		static double xAccelValue;
		static double yAccelValue;
		static double zAccelValue;
		
	public:
		static double getXAccelValue();
		static double getYAccelValue();
		static double getZAccelValue();
		static void setAccelValue(double x, double y, double z);
		
		static void setupAccelerometer(int updatesPerSecond); 

	};
}
#endif
		

