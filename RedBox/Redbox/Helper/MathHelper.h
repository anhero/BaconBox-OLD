/**
 * @file
 * @ingroup Helper
 * @ingroup Math
 */
#ifndef RB_MATHHELPER_H
#define RB_MATHHELPER_H

namespace RedBox {
	/**
	 * Math utilities. Class containing functions used for math operations.
	 * @ingroup Helper
	 * @ingroup Math
	 */
	class MathHelper {
	public:
		/**
		 * Gets the next power of 2. Takes a number and finds the closest power
		 * of 2 that's higher.
		 * @param number Number for which to find the next power of 2 that's
		 * higher.
		 * @return Next power of 2 of the given number.
		 */
		static int nextPowerOf2(int number);
		/**
		 * Does a modulo on the two floats recieved.
		 * @param dividend Dividend of the modulo.
		 * @param divisor Divisor of the modulo.
		 * @return Remainder from the division.
		 */
		static float modFloat(float dividend, float divisor);

		static float degreesToRadians(float degrees);
	};
}
#endif
