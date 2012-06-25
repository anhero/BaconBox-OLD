/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_IS_SAME_H
#define RB_IS_SAME_H

namespace BaconBox {
	/**
	 * Used to statically check if two types are the same.
	 * @tparam T First type to compare.
	 * @tparam S Second type to compare.
	 * @ingroup Helper
	 */
	template <typename T, typename S>
	struct IsSame {
		static const bool RESULT = false;
	};

	template <typename T>
	struct IsSame<T, T> {
		static const bool RESULT = true;
	};
}

#endif // RB_IS_SAME_H
