#include "BaconBox/Helper/TimeHelper.h"

#include "BaconBox/PlatformFlagger.h"

#ifdef RB_TIME_HELPER_INCLUDE
#include RB_TIME_HELPER_INCLUDE
#endif

using namespace BaconBox;

TimeHelper& TimeHelper::getInstance() {
	static RB_TIME_HELPER_IMPL instance;
	return instance;
}

double TimeHelper::getSinceStart(TimeType timeType) const {
	switch(timeType) {
	case SCALABLE_PAUSABLE:
		return getSinceStartScalablePausable();
		break;
	case PAUSABLE:
		return getSinceStartPausable();
		break;
	case COMPLETE:
		return getSinceStartComplete();
		break;
	default:
		return getSinceStartComplete();
		break;
	}
}

double TimeHelper::getSinceStartScalablePausable() const {
	return sinceStart;
}

double TimeHelper::getSinceStartPausable() const {
	return sinceStartReal;
}

double TimeHelper::getSinceStartComplete() const {
	return sinceStartComplete;
}

double TimeHelper::getTimeScale() const {
	return timeScale;
}

void TimeHelper::setTimeScale(double newTimeScale) {
	timeScale = newTimeScale;
}

void TimeHelper::pause() {
	paused = true;
}

void TimeHelper::unpause() {
	paused = false;
}

bool TimeHelper::isPaused() const {
	return paused;
}

TimeHelper::TimeHelper() : sinceStart(0.0), sinceStartReal(0.0),
sinceStartComplete(0.0), timeScale(1.0), paused(false) {
}

TimeHelper::~TimeHelper() {
}
