/**
 * @file
 * @ingroup Helper
 */
#ifndef __TIMEHELPER_H
#define __TIMEHELPER_H

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
	private:
		/// Number of seconds since the epoch.
		static double epoch;
    };
}

#endif