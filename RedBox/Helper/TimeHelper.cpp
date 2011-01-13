#include "TimeHelper.h"
//Pour linux et POSIX en général:
#ifdef LINUX
#include <sys/time.h>
#endif

#ifdef _WIN32 // Defined by all Windows 32 compilers, but not by any others.
#include <windows.h>
#endif //_WIN32

using namespace RedBox;

double TimeHelper::epoch = 0.0;

void TimeHelper::refreshTime() {
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	epoch = [[NSDate date] timeIntervalSince1970];
	[pool release];
#endif //Target iPhone
#endif //__APPLE__
	
#ifdef __linux__
	//Defines a timespec to hold the time
	timespec currTime;
	//Get the time and put it in the timespec
	clock_gettime(CLOCK_REALTIME, &currTime);
	//Stores the seconds
	epoch = currTime.tv_sec;
	//TODO: See if it is possible and wise to actually keep precision tightly...
	//Then gets the nanoseconds after the comma
	epoch += (currTime.tv_nsec)/1000000000.0;
#endif //LINUX
	
#ifdef _WIN32
	//_SYSTEMTIME sysTime = GetSystemTime();
	//epoch = static_cast<double>((sysTime.wYear - 1970) * 31536000 + );
#endif //_WIN32
}

double TimeHelper::getSinceEpoch() {
	return epoch;
}