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

		/**
		 * Converts the given number in degrees to radian.
		 * @param degrees Angle in degrees to convert.
		 * @return Angle converted to radian.
		 */
		static float degreesToRadians(float degrees);
		
		/// Constant for PI.
		static const float PI;

		/**
		 * Executes a division, but rounds up instead of down.
		 * @param dividend Division's dividend.
		 * @param divisor Division's divisor.
		 * @return Quotient rounded up if it would have decimals.
		 */
		static unsigned int roundUpDivision(unsigned int dividend,
											unsigned int divisor);
		
	private:
		/// Constant used for converting degrees to radians.
		static const float DEGREE_TO_RADIAN;
		
	};
}
#endif
