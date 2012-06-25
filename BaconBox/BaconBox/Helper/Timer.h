/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TIMER_H
#define RB_TIMER_H

#include <sigly.h>

namespace BaconBox {
	/**
	 * Timer class. Sends a signal at every interval until stopped.
	 * @ingroup Helper
	 */
	class Timer {
		friend class TimerManager;
	public:
		/**
		 * Signal sent when the timer ticks. Connect a function to this signal
		 * to have it be called when the timer ticks.
		 */
		sigly::Signal0<> tick;
		/**
		 * Default constructor, starts with an interval of 0 seconds. Connects
		 * itself with the timer manager.
		 */
		Timer();
		/**
		 * Parameterized constructor. Connects itself to the timer manager.
		 * @param newInterval Time interval between each tick (in seconds).
		 */
		Timer(double newInterval);
		/**
		 * Destructor. Disconnects itself from the timer manager.
		 */
		~Timer();
		/**
		 * Starts the timer. The first tick is called after the first interval.
		 */
		void start();
		/**
		 * Stops the timer.
		 */
		void stop();
		/**
		 * Checks whether the timer is started or not.
		 * @return True if the timer is started, false if not.
		 */
		bool isStarted() const;
		/**
		 * Sets the timer's interval between each tick.
		 * @param newInterval Time between each ticks (in seconds).
		 */
		void setInterval(double newInterval);
		/**
		 * Gets the time interval between each tick.
		 * @return Time interval between each tick.
		 */
		double getInterval() const;
	private:
		/// Set to true when the timer is started, false otherwise.
		bool started;
		/// Time interval to have between each tick.
		double interval;
		/// Internal time counter used to know when to shoot tick signals.
		double timeCounter;
		/**
		 * Updates the timer.
		 */
		void update();
	};
}

#endif
