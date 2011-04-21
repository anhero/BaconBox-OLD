/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TIMEHELPER_H
#define RB_TIMEHELPER_H

namespace RedBox {
	/**
	 * Class used to get information about the time. It's a singleton.
	 * @ingroup Helper
	 */
	class TimeHelper {
		friend class RedBoxEngine;
	public:
		/**
		 * Gets TimeHelper's instance.
		 */
		static TimeHelper* getInstance();
		/**
		 * Gets the time since the game was started (in seconds). Takes into
		 * account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		virtual double getSinceStart() const = 0;
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		virtual double getSinceStartReal() const = 0;
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		virtual double getSinceStartComplete() const = 0;
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
	protected:
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
		/// TimeHelper's instance.
		static TimeHelper* instance;
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