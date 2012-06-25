/**
 * @file
 * @ingroup Math
 * @ingroup Helper
 */
#ifndef RB_MATH_HELPER_H
#define RB_MATH_HELPER_H

#include <cstddef>
#include <climits>

#include "StaticAssert.h"
#include "IsNumber.h"
#include "Ease.h"

namespace BaconBox {
	/**
	 * Math utilities. Class containing functions used for math operations.
	 * @ingroup Math
	 * @ingroup Helper
	 */
	class MathHelper {
	public:
		template <typename T>
		struct AngleConvert {
			/**
			 * Multiply this constant by an angle in radians to convert it into
			 * degrees.
			 */
			static const T RADIANS_TO_DEGREES;
			
			/**
			 * Multiply this constant by an angle in degrees to convert it into
			 * radians.
			 */
			static const T DEGREES_TO_RADIANS;
		};
		/**
		 * Constant for PI. Usage: MathHelper::PI<float> to get PI as a float,
		 * MathHelper::PI<double> to get PI as a double and
		 * MathHelper::PI<long double> to get PI as a long double.
		 */
		template <typename T>
		struct PI {
			/**
			 * Cast operator overload to cast the PI type into a float, a double
			 * or a long double (depending on the template parameter).
			 */
			operator T();
		};
		
		/**
		 * Gets the next power of 2. Takes a number and finds the closest power
		 * of 2 that's higher.
		 * @param number Number for which to find the next power of 2 that's
		 * higher.
		 * @return Next power of 2 of the given number.
		 */
		template <typename T>
		static T nextPowerOf2(T number) {
			typedef typename StaticAssert<IsIntegerNumber<T>::RESULT>::Result Test;
			if(number == 0) {
				return 1;
			}
			
			--number;
			for (size_t i = 1; i < sizeof(T) * CHAR_BIT; i <<= 1) {
				number = number | number >> i;
			}
			return number + 1;
		}
		
		/**
		 * Executes a division, but rounds up instead of down.
		 * @param dividend Division's dividend.
		 * @param divisor Division's divisor.
		 * @return Quotient rounded up if it would have decimals.
		 */
		template <typename T>
		static T roundUpDivision(T dividend, T divisor) {
			typedef typename StaticAssert<IsIntegerNumber<T>::RESULT>::Result Test;
			return ((dividend % divisor) ? (dividend / divisor + 1) : (dividend / divisor));
		}
		
		/**
		 * Clamps a number within a specific range.
		 * @param x Value to clamp.
		 * @param a Lower boundary of the range to clamp within.
		 * @param b Higher boundary of the range to clamp within.
		 * @return Clamped value, either x, a or b.
		 */
		template <typename T>
		static T clamp(T x, T a, T b) {
			return (x < a) ? (a) : ((x > b) ? (b) : (x));
		}
		
		/**
		 * Checks if two numbers have the same sign.
		 * @param x First number to check.
		 * @param y Second number to check.
		 */
		template <typename T>
		static bool sameSign(T x, T y) {
			return ((x < T()) == (y < T()));
		}

		/**
         * Eases a value using a specific type of easing.
         * @param t Value to ease.
         * @param easeType Type of easing to apply.
         * @param b Value to add to the easing.
         * @param c Force to apply on the easing.
         * @param d Force to apply on the easing.
         */
        static float ease(float t, Ease easeType, float b = 0.0f,
                          float c = 1.0f, float d = 1.0f);

		/**
		 * Gives the equivalent angle in the range from -180 to 180 degrees.
		 * @param angle Angle to make sure is from -180 to 180.
		 * @return The angle converted to be from -180 to 180.
		 * @tparam T Type of the angle, either int or float.
		 */
		template <typename T>
		static T clampAngle(T angle);

		/**
		 * Calculates the distance between two one-dimensional segments.
		 * @return Distance between the two segments. Negative value if they
		 * overlap.
		 */
		template <typename T>
		static T distance(T minA, T maxA, T minB, T maxB) {
			return (minA < minB) ? (minB - maxA) : (minA - maxB);
		}

	private:
		MathHelper();
	};
}

#endif
