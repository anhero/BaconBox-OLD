#include "BaconBox/Helper/Timer.h"

#include "BaconBox/Engine.h"
#include "BaconBox/Helper/TimerManager.h"

using namespace BaconBox;

Timer::Timer() : started(false), interval(0.0), timeCounter(0.0) {
	TimerManager::addTimer(this);
}

Timer::Timer(double newInterval) : started(false), interval(newInterval),
timeCounter(0.0) {
	TimerManager::addTimer(this);
}

Timer::~Timer() {
	TimerManager::removeTimer(this);
}

void Timer::start() {
	started = true;
	timeCounter = 0.0;
}

void Timer::stop() {
	started = false;
}

bool Timer::isStarted() const {
	return started;
}

void Timer::setInterval(double newInterval) {
	interval = newInterval;
}

double Timer::getInterval() const {
	return interval;
}

void Timer::update() {
	if(started) {
		timeCounter += Engine::getSinceLastUpdate();
		while(timeCounter > interval) {
			timeCounter -= interval;
			tick();
		}
	}
}

