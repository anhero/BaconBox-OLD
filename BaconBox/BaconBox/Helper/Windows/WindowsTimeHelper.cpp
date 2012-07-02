#include "BaconBox/PlatformFlagger.h"

#ifdef RB_WIN32

#include "BaconBox/Helper/Windows/WindowsTimeHelper.h"

using namespace BaconBox;

void WindowsTimeHelper::sleep(double duration) {
	Sleep(static_cast<unsigned int>(duration * 1000.0));
}

WindowsTimeHelper::WindowsTimeHelper() : TimeHelper() {
	startTime = GetTickCount();
}

WindowsTimeHelper::~WindowsTimeHelper() {
}

void WindowsTimeHelper::refreshTime() {
	ULONGLONG currentTime = GetTickCount();
	ULONGLONG tmp;
	
	// We add time to sinceStart and sinceStartReal only if the game isn't
	// paused.
	if(!isPaused()) {
		// We get the time since the last refresh.
		tmp = currentTime - lastTime;
		// We convert it into a double.
		double sinceLast = nbSecsFromULongLong(tmp);
		// We add this time to sinceStart while taking into account the time
		// scaling.
		sinceStart += sinceLast * getTimeScale();
		// We add this time to the sinceStartReal.
		sinceStartReal += sinceLast;
	}
	
	// We calculate the time since the game started.
	tmp = currentTime - startTime;
	sinceStartComplete = nbSecsFromULongLong(tmp);
	
	lastTime = currentTime;
}
double WindowsTimeHelper::nbSecsFromULongLong(ULONGLONG ticks) {
	return static_cast<double>(ticks / 1000LL) +
	static_cast<double>(ticks % 1000LL) / 1000.0;
}

#endif
