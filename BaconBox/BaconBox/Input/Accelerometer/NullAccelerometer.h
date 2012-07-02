/**
 * @file
 * @ingroup Input
 */
#ifndef RB_NULL_ACCELEROMETER_H
#define RB_NULL_ACCELEROMETER_H

#include "BaconBox/Input/Accelerometer/Accelerometer.h"

namespace BaconBox {
	/**
	 * Null accelerometer device. Used when the platform doesn't have an
	 * accelerometer device.
	 * @ingroup Input
	 */
	class NullAccelerometer : public Accelerometer {
	public:
		/**
		 * Default constructor.
		 */
		NullAccelerometer();

		/**
		 * Destructor.
		 */
		~NullAccelerometer();

		/**
		 * Update the null accelerometer device.
		 */
		void updateDevice();
	};

}

#endif // RB_NULL_ACCELEROMETER_H
