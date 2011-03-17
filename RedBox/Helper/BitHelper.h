/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_BIT_HELPER_H
#define RB_BIT_HELPER_H

#include <stdint.h>

namespace RedBox {
	/**
	 * Contains functions related to bits and bytes.
	 */
	class BitHelper {
	public:
		/**
		 * Checks if the system is in big endian or not.
		 * @return True if the system is in big endian, false if not.
		 */
		static bool isBigEndian();
		/**
		 * Swap endian on a 16 bits variable.
		 * @param x Variable to have its endian swapped.
		 */
		static void endianSwap(uint16_t& x);
		/**
		 * Swap endian on a 32 bits variable.
		 * @param x Variable to have its endian swapped.
		 */
		static void endianSwap(uint32_t& x);
		/**
		 * Swap endian on a 64 bits variable.
		 * @param x Variable to have its endian swapped.
		 */
		static void endianSwap(uint64_t& x);
		/**
		 * Gets the variable's value with its endian swapped.
		 * @param x Variable to have its endian swapped.
		 * @return Endian swapped value.
		 */
		static uint16_t otherEndian(uint16_t x);
		/**
		 * Gets the variable's value with its endian swapped.
		 * @param x Variable to have its endian swapped.
		 * @return Endian swapped value.
		 */
		static uint32_t otherEndian(uint32_t x);
		/**
		 * Gets the variable's value with its endian swapped.
		 * @param x Variable to have its endian swapped.
		 * @return Endian swapped value.
		 */
		static uint64_t otherEndian(uint64_t x);
	};
}
#endif
