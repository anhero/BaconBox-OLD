#import "RBAccelerometerDelegate.h"

using namespace RedBox;


@implementation RBAccelerometerDelegate

static RBAccelerometerDelegate * accelDelegateSingleton;


- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	Accelerometer::setAccelValue(acceleration.x, acceleration.y, acceleration.z);
}

+ (RBAccelerometerDelegate*)getAccelDelegate{
	return accelDelegateSingleton;
}

+(void) initialize
{
        accelDelegateSingleton = [[RBAccelerometerDelegate alloc] init];
}
@end
