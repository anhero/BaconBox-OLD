#include "BaconBox/PlatformFlagger.h"

#if defined(RB_MAC_PLATFORM) || defined(RB_LINUX)

#include "BaconBox/Helper/libc/LibcTimeHelper.h"

#include <unistd.h>
#include <cmath>

using namespace BaconBox;

LibcTimeHelper::LibcTimeHelper() : TimeHelper() {
	gettimeofday(&startTime, 0);
	gettimeofday(&lastTime, 0);
}

LibcTimeHelper::~LibcTimeHelper() {
}

void LibcTimeHelper::refreshTime() {
	timeval currentTime;
	// We get the current time.
	gettimeofday(&currentTime, 0);
	timeval tmp;

	// We add time to sinceStart and sinceStartReal only if the game isn't
	// paused.
	if(!isPaused()) {
		// We get the time since the last refresh.
		timevalSubstract(currentTime, lastTime, tmp);
		// We convert it into a double.
		double sinceLast = getNbSecsFromTimeval(tmp);
		// We add this time to sinceStart while taking into account the time
		// scaling.
		sinceStart += sinceLast * getTimeScale();
		// We add this time to the sinceStartReal.
		sinceStartReal += sinceLast;
	}
	
	// We calculate the time since the game started.
	timevalSubstract(currentTime, startTime, tmp);
	sinceStartComplete = getNbSecsFromTimeval(tmp);

	// We refresh the lastTime variable.
	lastTime = currentTime;
}

void LibcTimeHelper::sleep(double duration) {
	::sleep(static_cast<unsigned int>(floor(duration)));
	::usleep(static_cast<unsigned int>(fmod(duration, floor(duration)) * 1000.0) * 1000);
}

void LibcTimeHelper::timevalSubstract(timeval& x, timeval& y, timeval& result) {
	/* Perform the carry for the later subtraction by updating y. */
	if (x.tv_usec < y.tv_usec) {
		int nsec = (y.tv_usec - x.tv_usec) / 1000000 + 1;
		y.tv_usec -= 1000000 * nsec;
		y.tv_sec += nsec;
	}
	if (x.tv_usec - y.tv_usec > 1000000) {
		int nsec = (x.tv_usec - y.tv_usec) / 1000000;
		y.tv_usec += 1000000 * nsec;
		y.tv_sec -= nsec;
	}
	
	/* Compute the time remaining to wait.
	 tv_usec is certainly positive. */
	result.tv_sec = x.tv_sec - y.tv_sec;
	result.tv_usec = x.tv_usec - y.tv_usec;
	
}

double LibcTimeHelper::getNbSecsFromTimeval(const timeval& tv) {
	return static_cast<double>(tv.tv_sec) +
	static_cast<double>(tv.tv_usec) / 1000000.0;
}

#endif
