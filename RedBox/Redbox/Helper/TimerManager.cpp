#include "TimerManager.h"

#include <cassert>

#include "Timer.h"

using namespace RedBox;

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
	for(std::set<Timer*>::iterator i = timers.begin(); i != timers.end(); ++i) {
		if(*i) {
			(*i)->update();
		}
	}
}

TimerManager::TimerManager() {
}
