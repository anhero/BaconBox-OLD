/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TIMER_MANAGER_H
#define RB_TIMER_MANAGER_H

#include <set>

namespace RedBox {
	class Timer;
	/**
	 * Internal manager for the timers. Only the Timer and RedBoxEngine classes
	 * have access to this class's functions.
	 * @ingroup Helper
	 */
	class TimerManager {
		friend class Timer;
		friend class RedBoxEngine;
	private:
		/// Set containing pointers to the timers that need updating.
		static std::set<Timer*> timers;
		/**
		 * Adds a timer to the timer manager.
		 * @param timer Pointer to the timer to add.
		 */
		static void addTimer(Timer* timer);
		/**
		 * Removes a timer from the timer manager.
		 * @param timer Pointer to the timer to remove from the timer manager.
		 */
		static void removeTimer(Timer* timer);
		/**
		 * Updates the timers.
		 */
		static void update();
		/**
		 * Private default constructor to make sure no one instantiates this
		 * class.
		 */
		TimerManager();
	};
}

#endif
