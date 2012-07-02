#include "BaconBox/Helper/TimerManager.h"

#include <cassert>
#include <algorithm>

#include "BaconBox/Helper/Timer.h"

using namespace BaconBox;

std::set<Timer*> TimerManager::timers = std::set<Timer*>();

void TimerManager::addTimer(Timer* timer) {
	assert(timer);
	timers.insert(timer);
}

void TimerManager::removeTimer(Timer *timer) {
	assert(timer);
	timers.erase(timer);
}

void TimerManager::update() {
	// We update the timers.
	std::for_each(timers.begin(), timers.end(), TimerManager::updateTimer);
}

void TimerManager::updateTimer(Timer *timer) {
	if(timer) {
		timer->update();
	}
}

TimerManager::TimerManager() {
}
