#ifndef RB_WINDOWS_TIME_HELPER_H
#define RB_WINDOWS_TIME_HELPER_H

#include "PlatformFlagger.h"

#ifdef RB_WINDOWS

#include <windows.h>

#include "TimeHelper.h"

namespace RedBox {
	class WindowsTimeHelper : public TimeHelper {
		friend class TimeHelper;
	private:
		/// Time at which TimeHelper was initialized.
		ULONGLONG startTime;
		/// Last time the TimeHelper was refreshed.
		ULONGLONG lastTime;
		/**
		 * Default constructor.
		 */
		WindowsTimeHelper();
		/**
		 * Destructor.
		 */
		~WindowsTimeHelper();
		/**
		 * Refreshes the time variable.
		 */
		void refreshTime();
		/**
		 * Gets the number of seconds from a ULONGLONG.
		 * @param ticks ULONGLONG to calculate the number of seconds from.
		 * @return Double containing the number of seconds with the
		 * microseconds.
		 */
		double nbSecsFromULongLong(ULONGLONG ticks);
	};
}

#endif

#endif