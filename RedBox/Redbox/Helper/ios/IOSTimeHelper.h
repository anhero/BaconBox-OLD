#ifndef RB_IOS_TIME_HELPER_H
#define RB_IOS_TIME_HELPER_H

#include "PlatformFlagger.h"

#ifdef RB_IPHONE_PLATFORM

#include "TimeHelper.h"

namespace RedBox {
	class IOSTimeHelper : public TimeHelper {
		friend class TimeHelper;
	public:
		void sleep(double duration);
	private:
		/// Time at which TimeHelper was initialized.
		double startTime;
		/// Last time the TimeHelper was refreshed.
		double lastTime;
		/**
		 * Default constructor.
		 */
		IOSTimeHelper();
		/**
		 * Destructor.
		 */
		~IOSTimeHelper();
		/**
		 * Refreshes the time variable.
		 */
		void refreshTime();
	};
}

#endif

#endif