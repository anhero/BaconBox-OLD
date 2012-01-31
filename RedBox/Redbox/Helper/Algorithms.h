#ifndef RB_ALGORITHMS_H
#define RB_ALGORITHMS_H

#include <algorithm>
#include <iterator>
#include <list>

namespace RedBox {
	template <typename RandomAccessIterator>
	void riffleShuffle(RandomAccessIterator first, RandomAccessIterator last) {
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
}

#endif
