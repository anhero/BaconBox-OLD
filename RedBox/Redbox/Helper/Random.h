/**
 * @file
 * @ingroup Helper
 */

#ifndef __RANDOMGENERATOR_H
#define __RANDOMGENERATOR_H

#include <cstdlib>

namespace RedBox {
	
	/**
	 * Random number generator. Class used to generate random values.
	 * @ingroup Helper
	 */
	class Random {
	public:
		/**
		 * Generates a random integer. The number generated will inclusively be
		 * between the min and the max recieved.
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
		 * between the min and the max recieved.
		 * @param min Minimum value the generated number can have.
		 * @param max Maximum value the generated number can have.
		 * @return Number generated randomly between min and max (inclusively).
		 */
		static double getRandomDouble(double min, double max);
	private:
		/// Maximum double value.
		static double D_RAND_MAX;
	};
	
}

#endif
