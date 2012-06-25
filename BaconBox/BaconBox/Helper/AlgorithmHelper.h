/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_ALGORITHMS_H
#define RB_ALGORITHMS_H

#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <iterator>

namespace BaconBox {

	/**
	 * Contains functions to apply generic algorithms.
	 * @ingroup Helper
	 */
	class AlgorithmHelper {
	public:
		/**
		 * Does a riffle shuffle on a range of elements. The iterators must be
		 * random access iterators.
		 */
		template <typename RandomAccessIterator>
		static void riffleShuffle(RandomAccessIterator first, RandomAccessIterator last) {
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type int_type;
			int_type n = last - first;
			std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> tmp(n);
			std::copy(first, last, tmp.begin());
			int_type low = 0, high = n - 1, i = 0;

			while (i < n) {
				first[i] = tmp[low];
				++low;
				++i;

				if (i < n) {
					first[i] = tmp[high];
					--high;
					++i;
				}
			}
		}
		
		/**
		 * Checks if the given unary predicate returns true for all elements in
		 * the given range.
		 * @param first First element of the range to check.
		 * @param last Element after the last element to check.
		 * @param predicate Unary predicate to use. The signature should be
		 * equivalent to the following:
		 *    bool pred(const Type &a);
		 * The signature does not need to have "const &", but the function must
		 * not modify the objects passed to it. The type "Type" must be such
		 * that an object of type InputIterator can be dereferenced and then
		 * implicitely converted to Type.
		 * @return True if the unary predicate returns true for all elements
		 * in the range, false otherwise. Returns true if the range is empty.
		 */
		template <typename InputIterator, typename UnaryPredicate>
		static bool allOf(InputIterator first, InputIterator last,
						  UnaryPredicate predicate) {
			for (; first != last; ++first) {
				if (!predicate(*first)) return false;
			}
			return true;
		}
	private:
		/**
		 * Private undefined default constructor.
		 */
		AlgorithmHelper();
	};
}

#endif
