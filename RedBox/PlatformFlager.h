#ifdef __APPLE__
#include "TargetConditionals.h"
	#define RB_APPLE_PLATFORM
	#define RB_OPENGL
#ifdef TARGET_IPHONE_SIMULATOR 
	#define RB_IPHONE_PLATFORM
	#define RB_IPHONE_SIMULATOR_PLATFORM
#endif // TARGET_IPHONE_SIMULATOR

#ifdef TARGET_OS_IPHONE
	#define RB_IPHONE_PLATFORM
	#define RB_IPHONE_DEVICE_PLATFORM
#endif // TARGET_OS_IPHONE
#endif // __APPLE__