#ifndef __TIMEHELPER_H
#define __TIMEHELPER_H

namespace RedBox {
	class TimeHelper {
		static double epoch;
     public:
		static void refreshTime();
        static double getSinceEpoch();
    };
}

#endif