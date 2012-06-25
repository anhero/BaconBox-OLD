/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TIMEHELPER_H
#define RB_TIMEHELPER_H

namespace BaconBox {
	/**
	 * Class used to get information about the time. It's a singleton.
	 * @ingroup Helper
	 */
	class TimeHelper {
		friend class Engine;
	public:
		enum TimeType {
			SCALABLE_PAUSABLE,
			PAUSABLE,
			COMPLETE
		};

		/**
		 * Gets TimeHelper's instance.
		 */
		static TimeHelper& getInstance();
		/**
		 * Calls the respective getSinceStart...() functions from the enum
		 * type.
		 * @param timeType Type of time to get.
		 * @return Time since the game started either scaled or not and with
		 * the paused time counted or not.
		 */
		double getSinceStart(TimeType timeType = SCALABLE_PAUSABLE) const;
		/**
		 * Gets the time since the game was started (in seconds). Takes into
		 * account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		double getSinceStartScalablePausable() const;
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		double getSinceStartPausable() const;
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		double getSinceStartComplete() const;
		/**
		 * Gets the time scale.
		 * @return Time scale. 1.0 means it's at normal speed, 2.0 means it's
		 * going twice as fast.
		 */
		double getTimeScale() const;
		/**
		 * Sets the game's time scale. Usd to determine at which speed the game
		 * will go.
		 * @param newTimeScale Time scaling of the game.
		 */
		void setTimeScale(double newTimeScale);
		/**
		 * Pauses TimeHelper. Only getSinceStartComplete isn't influenced by
		 * the pausing/unpausing.
		 */
		void pause();
		/**
		 * Unpauses TimeHelper. Only getSinceStartComplete isn't influenced by
		 * the pausing/unpausing.
		 */
		void unpause();
		/**
		 * Checks if TimeHelper is paused.
		 * @return True if TimeHelper is paused, false if not.
		 */
		bool isPaused() const;
		/**
		 * Makes the game go to sleep for a specific time.
		 * @param duration Duration of the sleep.
		 */
		virtual void sleep(double duration) = 0;
	protected:
		/**
		 * Time in seconds since the TimeHelper was initialized. It is
		 * influenced by the time scaling and by the pausing/unpausing.
		 */
		double sinceStart;
		/**
		 * Time in seconds since the TimeHelper was initialized. It is
		 * not influenced by the time scaling, but is influenced by the
		 * pausing/unpausing.
		 */
		double sinceStartReal;
		/**
		 * Time in seconds since the TimeHelper was initialized. It is
		 * not influenced by the time scaling nor by the pausing/unpausing.
		 */
		double sinceStartComplete;
		/**
		 * Default constructor.
		 */
		TimeHelper();
		/**
		 * Destructor.
		 */
		virtual ~TimeHelper();
		/**
		 * Refreshes the time variable.
		 */
		virtual void refreshTime() = 0;
	private:
		/**
		 * Time scaling. The higher the value, the faster the time is being
		 * calculated.
		 */
		double timeScale;
		/// Set to true if TimeHelper is considered to be paused, false if not.
		bool paused;
    };
}

#endif
