#include "Accelerometer.h"

@interface RBAccelerometerDelegate : NSObject <UIAccelerometerDelegate>
{
}

+(RBAccelerometerDelegate*)getAccelDelegate;
@end
