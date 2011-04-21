#include "TimeHelper.h"

#include "PlatformFlagger.h"

#ifdef RB_TIME_HELPER_INCLUDE
#include RB_TIME_HELPER_INCLUDE
#endif

using namespace RedBox;

TimeHelper* TimeHelper::instance = 0;

TimeHelper* TimeHelper::getInstance() {
	if(!instance) {
		instance = RB_TIME_HELPER_IMPL;
	}
	return instance;
}

double TimeHelper::getSinceStart() const {
	return sinceStart;
}

double TimeHelper::getSinceStartReal() const {
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
