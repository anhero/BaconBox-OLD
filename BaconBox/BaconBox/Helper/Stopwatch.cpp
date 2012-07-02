#include "BaconBox/Helper/Stopwatch.h"

using namespace BaconBox;

Stopwatch::Stopwatch(): startTime(0.0), pausedTime(0.0),
	paused(false), started(false), timeType(TimeHelper::SCALABLE_PAUSABLE) {
}

Stopwatch::Stopwatch(const Stopwatch &src) : startTime(src.startTime),
	pausedTime(src.pausedTime), paused(src.paused), started(src.started),
	timeType(src.timeType) {
}

Stopwatch &Stopwatch::operator=(const Stopwatch &src) {
	if (this != &src) {
		startTime = src.startTime;
		pausedTime = src.pausedTime;
		paused = src.paused;
		started = src.started;
		timeType = src.timeType;
	}

	return *this;
}

void Stopwatch::start() {
	// We start the stopwatch.
	started = true;
	// We unpause the stopwatch.
	paused = false;
	// We get the current time.
	startTime = TimeHelper::getInstance().getSinceStart(timeType);
}

void Stopwatch::stop() {
	// We stop the stopwatch.
	started = false;
	// We unpause the timer.
	paused = false;
}

void Stopwatch::pause() {
	// If the stopwatch is running and isn't already paused.
	if (started && !paused) {
		// We pause the stopwatch.
		paused = true;
		// We calculate the time when the stopwatch was paused.
		pausedTime = TimeHelper::getInstance().getSinceStart(timeType) - startTime;
	}
}

void Stopwatch::unpause() {
	// If the stopwatch is paused.
	if (paused) {
		// We unpause the stopwatch.
		paused = false;
		// We recalculate the start time.
		startTime = TimeHelper::getInstance().getSinceStart(timeType) - pausedTime;
		// We reset the paused time.
		pausedTime = 0.0;
	}
}

double Stopwatch::getTime() const {
	// If the stopwatch is running.
	if (started) {
		// If the stopwatch is paused.
		if (paused) {
			// We return the time at which the stopwatch was paused.
			return pausedTime;

		} else {
			// We return the time since the stopwatch was started.
			return TimeHelper::getInstance().getSinceStart(timeType) - startTime;
		}
	}

	// If the timer isn't running.
	return 0.0;
}

bool Stopwatch::isStarted() const {
	return started;
}

bool Stopwatch::isPaused() const {
	return paused;
}

void Stopwatch::useScalablePausableTime() {
	if (!started) {
		timeType = TimeHelper::SCALABLE_PAUSABLE;
	}
}

void Stopwatch::usePausableTime() {
	if (!started) {
		timeType = TimeHelper::PAUSABLE;
	}
}

void Stopwatch::useCompleteTime() {
	if (!started) {
		timeType = TimeHelper::COMPLETE;
	}
}

void Stopwatch::setTimeType(TimeHelper::TimeType newTimeType) {
	if (!started) {
		timeType = newTimeType;
	}
}

TimeHelper::TimeType Stopwatch::getTimeType() const {
	return timeType;
}

void Stopwatch::addToTime(double timeToAdd) {
	if (started) {
		if (paused) {
			pausedTime += timeToAdd;

		} else {
			startTime -= timeToAdd;
		}
	}
}
