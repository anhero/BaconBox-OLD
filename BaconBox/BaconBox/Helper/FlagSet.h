/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_FLAG_SET_H
#define RB_FLAG_SET_H

#include <set>

namespace BaconBox {
	/**
	 * Represents a flag set. The type of the flag can be anything (but mostly
	 * used with type safe enumerators).
	 * @ingroup Helper
	 */
	template <typename T>
	class FlagSet {
	public:
		/**
		 * Default constructor.
		 */
		FlagSet() {
		}

		/**
		 * Parameterized constructor. Makes the flag set start with a flag
		 * raised.
		 * @param bit First flag to put up when the flag set is initialized.
		 */
		explicit FlagSet(const T &bit) {
			set(bit);
		}

		/**
		 * Copy constructor.
		 * @param src Flag set to make a copy of.
		 */
		FlagSet(const FlagSet<T> &src) : bits(src.bits) {
		}

		/**
		 * Assignment operator overload.
		 * @param src Flag set to make a copy of.
		 * @return Reference to the modified flag set.
		 */
		FlagSet<T>& operator=(const FlagSet<T> &src) {
			if (this != &src) {
				bits = src.bits;
			}

			return *this;
		}

		/**
		 * Binary OR operator overload.
		 * @param other Flag set to combine with the instance.
		 * @return Flag set representing the two flag sets merged.
		 */
		FlagSet<T> operator|(const FlagSet<T> &other) const {
			FlagSet<T> result(*this);

			for (typename std::set<T>::const_iterator i = other.bits.begin(); i != other.bits.end(); ++i) {
				result.bits.insert(*i);
			}

			return result;
		}

		/**
		 * Binary OR operator overload.
		 * @param bit Flag to raise on the resulting flag set.
		 * @return A copy of the instance with the given flag raised.
		 */
		FlagSet<T> operator|(const T &bit) const {
			FlagSet<T> result(*this);
			result.set(bit);
			return result;
		}

		/**
		 * Binary OR assignment operator overload.
		 * @param src Flag set to merge with the instance.
		 * @return Reference to the modified flag set (the instance).
		 */
		FlagSet<T>& operator|=(const FlagSet<T> &src) {
			if (this != &src) {
				*this = *this | src;
			}

			return *this;
		}

		/**
		 * Binary OR assignment operator overload.
		 * @param bit Flag to raise on the current instance.
		 * @return Reference to the modified flag set (the instance).
		 */
		FlagSet<T>& operator|=(const T &bit) {
			set(bit);
			return *this;
		}

		/**
		 * Checks if two flag sets have the same flags raised.
		 * @param other Flag set to check equality with.
		 * @return True if the flag sets have the same flags raised, false if
		 * not.
		 */
		bool operator==(const FlagSet<T> &other) const {
			return bits == other.bits;
		}

		/**
		 * Checks if two flag sets have different flags raised.
		 * @param other Flag set to check inequality with.
		 * @return True if the flag sets have different flags raised, false if
		 * not.
		 */
		bool operator!=(const FlagSet<T> &other) const {
			return !(this->operator==(other));
		}

		/**
		 * Raises or lowers a flag.
		 * @param newBit Bit to be raised or lowered.
		 * @param value If set to true, it will raise the flag. If set to false,
		 * it will lower the flag.
		 */
		void set(const T &newBit, bool value = true) {
			if (value) {
				bits.insert(newBit);

			} else {
				bits.erase(newBit);
			}
		}

		/**
		 * Raises or lowers one or more flags.
		 * @param newBits Flag set to raise or lower on the current instance.
		 * @param value If set to true, it will raise the flags. If set to
		 * false, it will lower the flags.
		 */
		void set(const FlagSet<T> &newBits, bool value = true) {
			if (value) {
				for (typename std::set<T>::const_iterator i = newBits.bits.begin();
				     i != newBits.bits.end(); ++i) {
					bits.insert(*i);
				}

			} else {
				for (typename std::set<T>::const_iterator i = newBits.bits.begin();
				     i != newBits.bits.end(); ++i) {
					bits.erase(*i);
				}
			}
		}

		/**
		 * Lowers all the flags.
		 */
		void reset() {
			bits.clear();
		}

		/**
		 * Lowers one or more flags.
		 * @param bitsToRemove Flag set containing the flags to lower on the
		 * current instance.
		 */
		void reset(const FlagSet<T> &bitsToRemove) {
			set(bitsToRemove, false);
		}

		/**
		 * Lowers a flag.
		 * @param bitToRemove Flag to lower.
		 */
		void reset(const T &bitToRemove) {
			set(bitToRemove, false);
		}

		/**
		 * Checks if a bit is raised.
		 * @param bitToCheck Flag to check.
		 * @return True if the given flag is raised, false if not.
		 */
		bool isSet(const T &bitToCheck) const {
			return bits.find(bitToCheck) != bits.end();
		}

		/**
		 * Checks if one or more specific flags are raised.
		 * @param bitsToCheck Flags to check.
		 * @return True if all the flags from the flag set are raised in the
		 * current instance, false if not.
		 */
		bool areSet(const FlagSet<T> &bitsToCheck) const {
			bool result = true;
			typename std::set<T>::const_iterator i = bitsToCheck.bits.begin();

			while (result && i != bitsToCheck.bits.end()) {
				result = result && (bits.find(*i) != bits.end());
				++i;
			}

			return result;
		}

		/**
		 * Gets the number of raised flags.
		 * @return Number of flags that are raised.
		 */
		typename std::set<T>::size_type count() const {
			return bits.size();
		}
	private:
		/**
		 * If a flag is raised, it can be found in this set. If a flag is
		 * lowered, it cannot be found in this set. So to raise a flag, we add
		 * it to this set and to lower a flag, we remove it from this set.
		 */
		std::set<T> bits;
	};
}

#endif
