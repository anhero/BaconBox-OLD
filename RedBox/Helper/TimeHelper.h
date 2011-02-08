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
     public:
		/**
		 * Refreshes the variable getting the current time.
		 */
		static void refreshTime();
		/**
		 * Gets the time in seconds since the epoch.
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
		 * Gets the time since the game was started (in seconds).
		 * @return Time since the game was started (in seconds).
		 */
		static double getSinceStart();
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
		/// Time in seconds since the game started.
		static double sinceStart;
		/// Time scaling. Higher means slower.
		static double timeScale;
		/// Boolean indicating if the game is paused.
		static bool paused;
		TimeHelper();
		TimeHelper(const TimeHelper& src);
		~TimeHelper();
		TimeHelper& operator=(const TimeHelper& src);
    };
}

#endif