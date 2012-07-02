/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_LIBC_TIME_HELPER_H
#define RB_LIBC_TIME_HELPER_H

#include "BaconBox/PlatformFlagger.h"

#if defined(RB_MAC_PLATFORM) || defined(RB_LINUX)

#include <sys/time.h>

#include "BaconBox/Helper/TimeHelper.h"

namespace BaconBox {
	/**
	 * Class used to get information about the time under Mac OS X.
	 * @ingroup Helper
	 */
	class LibcTimeHelper : public TimeHelper {
		friend class TimeHelper;
	public:
		/**
		 * Makes the game go to sleep for a specific time.
		 * @param duration Duration of the sleep.
		 */
		void sleep(double duration);
	private:
		/// Time at which TimeHelper was initialized.
		timeval startTime;
		/// Last time the TimeHelper was refreshed.
		timeval lastTime;
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
		 * @param x Timeval to be subtracted.
		 * @param y Timeval to subtract.
		 * @result Result of the subtraction.
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
