/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_RANGE_H
#define RB_RANGE_H

#include <algorithm>

namespace BaconBox {
	/**
	 * Represents a range. A range has a minimum value and a maximum value. The
	 * maximum value is excluded from the range.
	 * @tparam ValueType Type of the value that represent the limits of the
	 * range.
	 * @ingroup Helper
	 */
	template <typename ValueType>
	struct Range {
		struct Comparator {
			bool operator() (const Range<ValueType> &first,
			                 const Range<ValueType> &second) const {
				return first.min < second.min && first.max <= second.max;
			}
		};

		/**
		 * Default constructor.
		 */
		Range() : min(0), max(0) {
		}

		/**
		 * Implicit constructor.
		 * @param center Value to set to both the min and the max values.
		 */
		Range(ValueType center) : min(center), max(center) {
		}

		/**
		 * Parameterized constructor.
		 * @param newMin Minimum value of the range.
		 * @param newMax Maximum value of the range (not included).
		 */
		Range(ValueType newMin, ValueType newMax) : min(newMin), max(newMax) {
		}

		/**
		 * Copy constructor.
		 * @param src Range to copy.
		 */
		Range(const Range &src) : min(src.min), max(src.max) {
		}

		/**
		 * Checks whether or not the received value fits within the range.
		 * @param value Value to check.
		 * @return True if the value fits within the range, false if not.
		 */
		bool isWithinRange(ValueType value) const {
			return value >= min && value < max;
		}

		/// Minimum value in the range (included).
		ValueType min;

		/// Maximum value in the range (excluded).
		ValueType max;
	};
}

#endif // RB_RANGE_H
