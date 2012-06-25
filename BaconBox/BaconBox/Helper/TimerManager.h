/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TIMER_MANAGER_H
#define RB_TIMER_MANAGER_H

#include <set>

namespace BaconBox {
	class Timer;
	/**
	 * Internal manager for the timers. Only the Timer and Engine classes
	 * have access to this class's functions.
	 * @ingroup Helper
	 */
	class TimerManager {
		friend class Timer;
		friend class Engine;
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
		 * Calls the update method on the given timer if the pointer isn't NULL.
		 * @param timer Pointer to the timer to update.
		 */
		static void updateTimer(Timer* timer);
		/**
		 * Private default constructor to make sure no one instantiates this
		 * class.
		 */
		TimerManager();
	};
}

#endif
