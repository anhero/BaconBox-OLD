/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_FLAG_SET_H
#define RB_FLAG_SET_H

#include <set>

namespace RedBox {
	template <typename T>
	class FlagSet {
	public:
		FlagSet() {
		}

		FlagSet(const T& bit) {
			set(bit);
		}

		FlagSet(const FlagSet<T>& src) : bits(src.bits) {
		}

		FlagSet<T>& operator=(const FlagSet<T>& src) {
			if(this != &src) {
				bits = src.bits;
			}

			return *this;
		}

		FlagSet<T> operator|(const FlagSet<T>& other) const {
			FlagSet<T> result(*this);

			for(typename std::set<T>::const_iterator i = other.bits.begin(); i != other.bits.end(); ++i) {
				result.bits.insert(*i);
			}

			return result;
		}

		FlagSet<T> operator|(const T& bit) const {
			FlagSet<T> result(*this);
			result.set(bit);
			return result;
		}

		FlagSet<T>& operator|=(const FlagSet<T>& src) {
			if(this != &src) {
				*this = *this | src;
			}

			return *this;
		}

		FlagSet<T>& operator|=(const T& bit) {
			set(bit);
			return *this;
		}

		void set(const T& newBit, bool value = true) {
			if(value) {
				bits.insert(newBit);
			} else {
				bits.erase(newBit);
			}
		}

		void set(const FlagSet<T>& newBits, bool value = true) {
			if(value) {
				for(typename std::set<T>::const_iterator i = newBits.bits.begin();
					i != newBits.bits.end(); ++i) {
					bits.insert(*i);
				}
			} else {
				for(typename std::set<T>::const_iterator i = newBits.bits.begin();
					i != newBits.bits.end(); ++i) {
					bits.erase(*i);
				}
			}
		}

		void reset() {
			bits.clear();
		}

		void reset(const FlagSet<T>& bitsToRemove) {
			set(bitsToRemove, false);
		}

		bool isSet(const T& bitToCheck) const {
			return bits.find(bitToCheck) != bits.end();
		}

		bool areSet(const FlagSet<T>& bitsToCheck) const {
			bool result = true;
			typename std::set<T>::const_iterator i = bitsToCheck.bits.begin();
			while(result && i != bitsToCheck.bits.end()) {
				result = result && (bits.find(*i) != bits.end());
			}
			return result;
		}

		size_t count() const {
			return bits.size();
		}
	private:
		std::set<T> bits;
	};
}

#endif
