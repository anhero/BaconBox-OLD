/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_STOPWATCH_H
#define RB_STOPWATCH_H

#include "BaconBox/Helper/TimeHelper.h"

namespace BaconBox {
	/**
	 * Class that can be used like a simple stopwatch. Measures the time since
	 * it was started. It can be paused, resumed and restarted.
	 * @ingroup Helper
	 */
	class Stopwatch {
	public:
		/**
		 * Default constructor.
		 */
		Stopwatch();

		/**
		 * Copy constructor.
		 * @param src Stopwatch to copy.
		 */
		Stopwatch(const Stopwatch &src);

		/**
		 * Assignment operator overload.
		 * @param src Stopwatch to copy.
		 * @return Reference to the modified Stopwatch.
		 */
		Stopwatch &operator=(const Stopwatch &src);

		/**
		 * Starts the stopwatch, resets from whatever state the stopwatch was
		 * in and is restarted.
		 */
		void start();

		/**
		 * Stops the stopwatch. Time is reset at 0.
		 */
		void stop();

		/**
		 * Pauses the stopwatch. Stops counting time. When unpaused, time will
		 * continue to count from when it was paused. Does nothing if the
		 * stopwatch isn't started or is paused.
		 */
		void pause();

		/**
		 * Unpauses the stopwatch. If it was paused, it will restart from the
		 * time at which it was paused. Does nothing if the stopwatch wasn't
		 * paused.
		 */
		void unpause();

		/**
		 * Gets the stopwatch's time.
		 * @return If it isn't started, it returns 0. If the timer is paused,
		 * it returns the time when it was paused.
		 */
		double getTime() const;

		/**
		 * Gets whether the stopwatch is started or not.
		 * @return True if the stopwatch is started, even if it's paused.
		 * False if not.
		 */
		bool isStarted() const;

		/**
		 * Gets whether the stopwatch is paused or not.
		 * @return True if the stopwatch is started but paused, false if not.
		 */
		bool isPaused() const;

		/**
		 * Sets the stopwatch to use the scalable and pausable time. Can only
		 * be changed when the stopwatch is not started.
		 */
		void useScalablePausableTime();

		/**
		 * Sets the stopwatch to use the unscalable but pausable time. Can
		 * only be changed when the stopwatch is not started.
		 */
		void usePausableTime();

		/**
		 * Sets the stopwatch to use the unscalable and unpausable time. Can
		 * only be changed when the stopwatch is not started.
		 */
		void useCompleteTime();

		/**
		 * Sets the stopwatch's type of time to use. Can only be changed when
		 * the stopwatch is not started.
		 * @param newTimeType New type of time to use.
		 */
		void setTimeType(TimeHelper::TimeType newTimeType);


		/**
		 * Gets the type of time the stopwatch is currently using.
		 * @return Type of time the stopwatch is using.
		 */
		TimeHelper::TimeType getTimeType() const;

		/**
		 * Adds time to the stopwatch.
		 * @param timeToAdd Time in seconds to add to the stopwatch.
		 */
		void addToTime(double timeToAdd);
	private:
		/// Time at which the stopwatch was started.
		double startTime;

		/// Time since the stopwatch started when it was paused.
		double pausedTime;

		/// Set to true if the stopwatch is paused, false if not.
		bool paused;

		/// Set to true if the stopwatch is started, false if not.
		bool started;

		/// Type of time the stopwatch is using.
		TimeHelper::TimeType timeType;
	};
}

#endif
