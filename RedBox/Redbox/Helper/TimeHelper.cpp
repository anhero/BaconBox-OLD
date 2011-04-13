#include "TimeHelper.h"

#include "PlatformFlagger.h"

#ifdef RB_LINUX
#include <time.h>
#endif

#ifdef RB_QT
#include <QDateTime>
#endif

#ifdef RB_WIN32
#include <windows.h>
#endif // RB_WIN32

#ifdef RB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

using namespace RedBox;

double TimeHelper::epoch = 0.0;
double TimeHelper::sinceStart = 0.0;
double TimeHelper::sinceStartReal = 0.0;
double TimeHelper::gameStart = 0.0;
double TimeHelper::timeScale = 1.0;
bool TimeHelper::paused = false;

void TimeHelper::refreshTime() {
	double lastEpoch = epoch;
	epoch = getRealEpoch();
	if(!paused) {
		sinceStart += timeScale * (epoch - lastEpoch);
		sinceStartReal += epoch - lastEpoch;
	}
}

double TimeHelper::getSinceEpoch() {
	return epoch;
}

void TimeHelper::pause() {
	paused = true;
}

void TimeHelper::unpause() {
	paused = false;
}

bool TimeHelper::isPaused() {
	return paused;
}

double TimeHelper::getSinceStart() {
	return sinceStart;
}

double TimeHelper::getSinceStartReal() {
	return sinceStartReal;
}

double TimeHelper::getSinceStartComplete() {
	return epoch - gameStart;
}

void TimeHelper::setTimeScale(double newTimeScale) {
	timeScale = newTimeScale;
}

double TimeHelper::getRealEpoch() {
	double result = 0.0;
#ifdef RB_QT
	qint64 mSecs = QDateTime::currentMSecsSinceEpoch();
	result = static_cast<double>(mSecs / 1000) + static_cast<double>(mSecs % 1000) / 1000.0;
#endif
#ifdef RB_IPHONE_PLATFORM
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	result = [[NSDate date] timeIntervalSince1970];
	[pool release];
#endif // RB_IPHONE_PLATFORM
	
#ifdef RB_LINUX
	//Defines a timespec to hold the time
	timespec currTime;
	//Get the time and put it in the timespec
	clock_gettime(CLOCK_REALTIME, &currTime);
	//Stores the seconds
	result = currTime.tv_sec;
	//TODO: See if it is possible and wise to actually keep precision tightly...
	//Then gets the nanoseconds after the comma
	result += (currTime.tv_nsec)/1000000000.0;
#endif //LINUX
	
#ifdef RB_WIN32
	static const double NB_SECS_MILLISECOND = 0.001;
#if 0
	static const double NB_SECS_YEAR = 31536000.0;
	static const double NB_SECS_LEAP_YEAR = 31622400.0;
	static const double NB_SECS_LONG_MONTH = 2678400.0;
	static const double NB_SECS_FEBRUARY = 2419200.0;
	static const double NB_SECS_LEAP_FEBRUARY = 2505600.0;
	static const double NB_SECS_SHORT_MONTH = 2592000.0;
	static const double NB_SECS_DAY = 86400.0;
	static const double NB_SECS_HOUR = 3600.0;
	static const double NB_SECS_MINUTE = 60.0;
	_SYSTEMTIME sysTime = GetSystemTime();
	result = 0.0;
	// We convert the years into seconds, we take into account the leap years.
	for (WORD i = 1970; i < sysTime.wYear; ++i) {
		if(i % 4) {
			result += NB_SECS_YEAR;
		} else {
			result += NB_SECS_LEAP_YEAR; 
		}
	}
	// We convert the months into seconds, we take into account if the current
	// year is a leap year.
	for(WORD i = 1; i < sysTime.wMonth; ++i) {
		if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
			result += NB_SECS_LONG_MONTH;
		} else if(i == 2) {
			if (sysTime.wYear % 4) {
				result += NB_SECS_FEBRUARY;
			} else {
				result += NB_SECS_LEAP_FEBRUARY;
			}
		} else {
			result += NB_SECS_SHORT_MONTH;
		}
	}
	// We calculate the rest of the year in seconds.
	result += NB_SECS_DAY * static_cast<double((sysTime.wDay - 1)) + NB_SECS_HOUR * static_cast<double>(sysTime.wHour) + NB_SECS_MINUTE * static_cast<double>(sysTime.wMinute) + static_cast<double>(sysTime.wSecond) + NB_SECS_MILLISECOND * static_cast<double>(sysTime.wMilliseconds);
#else // #if 0
	// Simpler way to get the number of seconds.
#if (_WIN32_WINNT == _WIN32_WINNT_VISTA)
	// Only available on Vista and later, wraps around after about 585 million
	// years, so no worries here...
	ULONGLONG ticks = GetTickCount64();
#else
	// Will wrap around after about 49.7 days. Might have to check to do
	// something about it.
	DWORD ticks = GetTickCount();
#endif
	// We convert the milliseconds in the format we want.
	result = static_cast<double>(ticks / 1000) + static_cast<double>(ticks % 1000) * NB_SECS_MILLISECOND;
#endif // #if 0
#endif // RB_WIN32
	return result;
}

void TimeHelper::init() {
	gameStart = getRealEpoch();
}

TimeHelper::TimeHelper() {
}

TimeHelper::TimeHelper(const TimeHelper& src) {
}

TimeHelper::~TimeHelper() {
}

TimeHelper& TimeHelper::operator=(const TimeHelper& src) {
	return *this;
}
