#ifndef RB_ALGORITHMS_H
#define RB_ALGORITHMS_H

#include <algorithm>
#include <iterator>
#include <list>

namespace RedBox {
	template <typename RandomAccessIterator>
	void riffleShuffle(RandomAccessIterator first, RandomAccessIterator last) {
		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type int_type;
		int_type i = 1;
		int_type n = last - first - 1;
		int_type highest = n;
		std::list<int_type> smalls;
		bool needsLowering = true;
		while (i < n) {
			if (i % 2) {
				if (i == smalls.front()) {
					smalls.front() = highest;
				}

				// We get a big number.
				if (highest - i > 1) {
					std::swap(first[i], first[highest]);
					smalls.push_back(highest);
					if (needsLowering) {
						--highest;
					} else {
						needsLowering = true;
					}
				} else if (highest - i == 1) {
					std::swap(first[i], first[highest]);
				} else { // highest == i
					highest = smalls.back();
				}

			} else {
				if (i == highest) {
					highest = smalls.front();
					needsLowering = false;
				}

				// We get a small number.
				if (smalls.front() - i > 1) {
					std::swap(first[i], first[smalls.front()]);
					smalls.push_back(smalls.front());
					smalls.pop_front();
				} else if (smalls.front() - i == 1) {
					std::swap(first[i], first[smalls.front()]);
					smalls.pop_front();
				} else { // smalls.front() == i
					smalls.pop_front();
				}
			}
			++i;
		}
	}
}

#endif
