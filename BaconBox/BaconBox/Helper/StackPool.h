/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_STACK_POOL_H
#define RB_STACK_POOL_H

#include <cstddef>
#include <vector>

namespace BaconBox {
	/**
	 * Represents a pool of objects, but organized as a stack.
	 * @tparam T Type of objets the pool contains.
	 * @see BaconBox::Pool
	 */
	template <typename T>
	class StackPool {
		typedef std::vector<T> DropletVector;
		typedef typename DropletVector::iterator Iterator;
	public:
		/// Type used for the size of the pool.
		typedef typename std::vector<T>::size_type SizeType;

		/**
		 * Constructor. Initializes the stack pool with a starting maximum
		 * number of objets it can contain. After initializing this number,
		 * the only way of changing it is to reset the whole pool.
		 * @param newMaxSize Starting maximum number of objects the pool can
		 * contain. Set to 0 by default.
		 */
		explicit StackPool(SizeType newMaxSize = 0) : droplets(newMaxSize),
			first(droplets.begin()) {
		}

		/**
		 * Gets a pointer to the first available element from the pool and marks
		 * it as unavailable.
		 * @return Pointer to the first available element. Null if there aren't
		 * any elements left.
		 */
		T *getFirst() {
			if (first != droplets.end()) {
				return &(*(first++));

			} else {
				return NULL;
			}
		}

		/**
		 * Frees the most recently activated item and places it back into the
		 * stack pool of available elements. It becomes the first available
		 * element.
		 */
		void freeLast() {
			if (first != droplets.begin()) {
				--first;
			}
		}

		/**
		 * Gets the number of active elements.
		 * @return Number of active elements.
		 */
		SizeType getSize() const {
			return first - droplets.begin();
		}

		/**
		 * Checks whether or not there is at least one element active.
		 * @return True if there is at least one element active, false if not.
		 */
		bool isEmpty() const {
			return first == droplets.begin();
		}

		/**
		 * Gets the maximum number of items the stack pool can have activated at
		 * the same time.
		 */
		SizeType getMaxSize() const {
			return droplets.size();
		}

		/**
		 * Frees all the active elements. Resets the pool to its initial state.
		 */
		void reset() {
			first = droplets.begin();
		}

		/**
		 * Resets the stack pool, but also changes its maximum size.
		 * @param newMaxSize Maximum number of objects the pool can
		 * contain.
		 * @see BaconBox::StackPool<T>::getMaxSize() const
		 * @see BaconBox::StackPool<T>::reset()
		 */
		void reset(SizeType newMaxSize) {
			droplets.resize(newMaxSize);
			reset();
		}

	private:
		/// Contains the elements used by the pool.
		DropletVector droplets;

		/// Iterator to the first available element in the pool.
		Iterator first;
	};
}

#endif
