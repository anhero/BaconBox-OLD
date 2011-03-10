/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TIMEHELPER_H
#define RB_TIMEHELPER_H

namespace RedBox {
	/**
	 * Class used to get information about the time.
	 * @ingroup Helper
	 */
	class TimeHelper {
		friend class RedBoxEngine;
	public:
		/**
		 * Refreshes the variable getting the current time.
		 */
		static void refreshTime();
		/**
		 * Gets the time in seconds since the epoch. The fractional part of the
		 * value represents the current second's time. For Windows, The time is
		 * the one since the system was started.
		 * @return Number of seconds since the epoch.
		 */
        static double getSinceEpoch();
		/**
		 * Pauses the game.
		 */
		static void pause();
		/**
		 * Unpauses the game.
		 */
		static void unpause();
		/**
		 * Checks if the game is paused.
		 * @return True if the game is set to paused, false if not.
		 */
		static bool isPaused();
		/**
		 * Gets the time since the game was started (in seconds). Takes into
		 * account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		static double getSinceStart();
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		static double getSinceStartReal();
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		static double getSinceStartComplete();
		/**
		 * Sets the game's time scale. Usd to determine at which speed the game
		 * will go.
		 * @param newTimeScale Time scaling of the game.
		 */
		static void setTimeScale(double newTimeScale);
		/**
		 * Gets the time scale.
		 */
		static double getTimeScale();
	private:
		/// Number of seconds since the epoch.
		static double epoch;
		/**
		 * Time in seconds since the game was started. The fractional part of
		 * the value represents the current second's time. Affected by the time
		 * scaling. Does not count the time while the game is paused. Mainly
		 * used for animations and other visual effects.
		 */
		static double sinceStart;
		/**
		 * Time in seconds since the game was started. The fractional part of
		 * the value represents the current second's time. Not affected by the
		 * time scaling. Does not count the time while the game is paused.
		 * Mainly used for knowing how much time the player has spent playing.
		 */
		static double sinceStartReal;
		/// Time at which the game was started (since the epoch, in seconds).
		static double gameStart;
		/**
		 * Used to scale at which speed the time since the game was started is
		 * going. For example, if timeScale is set at 0.5, sinceStart will
		 * increment two times slower than usual.
		 */
		static double timeScale;
		/// Boolean indicating if the game is paused.
		static bool paused;
		/**
		 * Gets the system's time since the epoch.
		 */
		static double getRealEpoch();
		/**
		 * Initializes the TimeHelper.
		 */
		static void init();
		TimeHelper();
		TimeHelper(const TimeHelper& src);
		~TimeHelper();
		TimeHelper& operator=(const TimeHelper& src);
    };
}

#endif