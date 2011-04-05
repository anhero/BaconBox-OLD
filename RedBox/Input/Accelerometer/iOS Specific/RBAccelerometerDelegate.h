#include "Accelerometer.h"

#include "PlatformFlagger.h"
#ifdef RB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif
@interface RBAccelerometerDelegate : NSObject <UIAccelerometerDelegate>
{
}

+(RBAccelerometerDelegate*)getAccelDelegate;
@end
