/**
 * @file
 * @ingroup Helper
 */

#ifndef RB_RANDOMGENERATOR_H
#define RB_RANDOMGENERATOR_H

#include <cstdlib>

namespace BaconBox {
	
	/**
	 * Random number generator. Class used to generate random values.
	 * @ingroup Helper
	 */
	class Random {
	public:
		/**
		 * Generates a random integer. The number generated will inclusively be
		 * between the min and the max received.
		 * @param min Minimum value the generated number can have.
		 * @param max Maximum value the generated number can have.
		 * @return Number generated randomly between min and max (inclusively).
		 */
		static int getRandomInteger(int min, int max);
		/**
		 * Generates a random boolean value.
		 * @return Boolean value either true or false (random).
		 */
		static bool getRandomBool();
		/**
		 * Generates a random double. The number generated will inclusively be
		 * between the min and the max received.
		 * @param min Minimum value the generated number can have.
		 * @param max Maximum value the generated number can have.
		 * @return Number generated randomly between min and max (inclusively).
		 */
		static double getRandomDouble(double min, double max);

		/**
		 * Generates a random float. The number generated will inclusively be
		 * between the min and the max received.
		 * @param min Minimum value the generated number can have.
		 * @param max Maximum value the generated number can have.
		 * @return Number generated randomly between min and max (inclusively).
		 */
		static double getRandomFloat(float min, float max);
	private:
		/// Maximum double value.
		static double D_RAND_MAX;
                /// Used to know if the random seed has been initialized or not.
                static bool initialized;
                static void init();
	};
	
}

#endif
