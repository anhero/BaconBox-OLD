/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_LIBC_TIME_HELPER_H
#define RB_LIBC_TIME_HELPER_H

#include "PlatformFlagger.h"

#if defined(RB_MAC_PLATFORM) || defined(RB_LINUX)

#include <sys/time.h>

#include "TimeHelper.h"

namespace RedBox {
	/**
	 * Class used to get information about the time under Mac OS X.
	 * @ingroup Helper
	 */
	class LibcTimeHelper : public TimeHelper {
		friend class TimeHelper;
	public:
		/**
		 * Gets the time since the game was started (in seconds). Takes into
		 * account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		double getSinceStart() const;
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is not counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		double getSinceStartReal() const;
		/**
		 * Gets the time since the game was started (in seconds). Does not take
		 * into account the time scaling. Time is counted while the game is
		 * paused. Depends on refreshTime() being called recently.
		 * @return Time since the game was started (in seconds).
		 */
		double getSinceStartComplete() const;
	private:
		/// Time at which TimeHelper was initialized.
		timeval startTime;
		/// Last time the TimeHelper was refreshed.
		timeval lastTime;
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
		LibcTimeHelper();
		/**
		 * Destructor.
		 */
		~LibcTimeHelper();
		/**
		 * Refreshes the time variable.
		 */
		void refreshTime();
		/**
		 * Substracts two timevals.
		 * @param x Timeval to be substracted.
		 * @param y Timeval to substract.
		 * @result Result of the substraction.
		 */
		static void timevalSubstract(timeval& x, timeval& y, timeval& result);
		/**
		 * Gets the number of seconds from a timeval.
		 * @param tv Timeval to calculate the number of seconds from.
		 * @return Double containing the number of seconds with the
		 * microseconds.
		 */
		static double getNbSecsFromTimeval(const timeval& tv);
	};
}

#endif
#endif