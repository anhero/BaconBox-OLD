/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_POOL_H
#define RB_POOL_H

#include <vector>
#include <set>

namespace BaconBox {
	/**
	 * Represents a simple pool. It is used to improve performance and memory
	 * use by reusing objects from a fixed pool instead of allocating and
	 * freeing individually. With this version of the pool (when the second
	 * template parameter equals "false", you cannot iterate through the active
	 * items.
	 * @tparam T Type the pool contains.
	 * @tparam ITERABLE Whether or not you want to be able to iterate through
	 * the active objects.
	 */
	template <typename T, bool ITERABLE = false>
	class Pool {
	private:
		/**
		 * Represents an item in the pool. It either contains the item or is
		 * available and points to the next available droplet. Points to NULL if
		 * it's the last available droplet.
		 */
		union Droplet {
			/**
			 * Default constructor, initializes the droplet as a NULL pointer.
			 */
			Droplet() : next(NULL) {
			}

			/// Value that will be used.
			T value;

			/**
			 * Pointer to the next available droplet, NULL if it's the last
			 * available droplet.
			 */
			Droplet *next;
		};

		/// Represents the type of the vector that contains the droplets.
		typedef std::vector<Droplet> DropletVector;
	public:
		/// Type used for counting the number of droplets.
		typedef typename std::vector<Droplet>::size_type SizeType;

		/**
		 * Constructor. Initializes the pool with the specified maximum size.
		 * The size can only be changed when the pool is empty, so
		 * initialize the pool carefully.
		 * @param newMaxSize New maximum size for the pool.
		 * @see BaconBox::Pool<T>::droplets
		 */
		explicit Pool(SizeType newMaxSize) : droplets(newMaxSize),
			first(&(*droplets.begin())), size(0) {
			// We initialize the droplets' pointers.
			init();
		}

		/**
		 * Gets an available item.
		 * @return Pointer to the first available item. It is not initialized
		 * yet.
		 */
		T *create() {
			// We make sure the pool is not completely used.
			if (first) {
				Droplet *newDroplet = first;
				first = newDroplet->next;

				++size;

				return &(newDroplet->value);

			} else {
				return NULL;
			}
		}

		/**
		 * Makes the given item available in the pool. Make sure you free up all
		 * allocated memory the item uses before calling this function.
		 * Remember that you can call the destructor manually if it is what you
		 * need.
		 * @param toRemove Pointer to the item to be available again.
		 */
		void remove(T *toRemove) {
			if (!droplets.empty() && size > 0) {
				Droplet *droplet = reinterpret_cast<Droplet *>(toRemove);

				// We make sure the droplet is from this pool.
				if (droplet >= &(*droplets.begin()) &&
				    droplet <= &(*(droplets.begin() + droplets.size() - 1))) {
					droplet->next = first;
					first = droplet;
					--size;
				}
			}
		}

		/**
		 * Checks whether or not this item is from the pool. It doesn't care if
		 * the item is available or not.
		 */
		bool isInPool(T *toCheck) {
			Droplet *droplet = reinterpret_cast<Droplet *>(toCheck);
			return !droplets.empty() && size > 0 && droplet >= &(*droplets.begin()) &&
			       droplet <= &(*(droplets.begin() + droplets.size() - 1));
		}

		/**
		 * Gets the number of items in use.
		 * @return Number of items in use and unavailable.
		 */
		SizeType getSize() const {
			return size;
		}

		/**
		 * Checks if the pool is empty or not.
		 * @return True if all of the pool's items are available, false if not.
		 */
		bool isEmpty() const {
			return !size;
		}

		/**
		 * Gets the maximum number of items the pool can use. Can be changed by
		 * resetting the pool.
		 * @return Maximum number of items the pool can use.
		 */
		SizeType getMaxSize() const {
			return droplets.size();
		}

		/**
		 * Resets the pool and makes all the items available again.
		 */
		void reset() {
			first = &(*droplets.begin());
			size = 0;
			init();
		}

		/**
		 * Resets the pool, makes all the items available again and changes the
		 * maximum number of items the pool can have.
		 */
		void reset(SizeType newMaxSize) {
			droplets.resize(newMaxSize);
			reset();
		}
	private:
		/**
		 * Initializes the pool's droplets so they are all available and
		 * correctly point to the next available droplet.
		 */
		void init() {
			for (typename DropletVector::iterator i = droplets.begin(); i != droplets.end(); ++i) {
				if (i + 1 != droplets.end()) {
					i->next = &(*(i + 1));
				}
			}
		}

		/// Contains all the available and unavailable items.
		DropletVector droplets;

		/// Pointer to the first available droplet.
		Droplet *first;

		/// Number of active droplets.
		SizeType size;
	};

	/**
	 * Represents a simple pool. It is used to improve performance and memory
	 * use by reusing objects from a fixed pool instead of allocating and
	 * freeing individually. With this version of the pool, you can iterate
	 * through the active items.
	 * @tparam T Type the pool contains.
	 */
	template <typename T>
	class Pool<T, true> {
	private:
		/**
		 * Represents an item in the pool. It either contains the item or is
		 * available and points to the next available droplet. Points to NULL if
		 * it's the last available droplet.
		 */
		union Droplet {
			/**
			 * Default constructor, initializes the droplet as a NULL pointer.
			 */
			Droplet() : next(NULL) {
			}

			/// Value that will be used.
			T value;

			/**
			 * Pointer to the next available droplet, NULL if it's the last
			 * available droplet.
			 */
			Droplet *next;
		};

		/// Represents the type of the vector that contains the droplets.
		typedef std::vector<Droplet> DropletVector;
	public:
		/// Type used for counting the number of droplets.
		typedef typename DropletVector::size_type SizeType;

		/// Type used to keep track of the active items.
		typedef std::set<T *> ActiveSet;

		/// Iterator used to iterate through active items.
		typedef typename ActiveSet::iterator Iterator;
		/// Const iterator used to iterate through active items.
		typedef typename ActiveSet::const_iterator ConstIterator;
		/// Iterator used to iterate in reverse through active items.
		typedef typename ActiveSet::reverse_iterator ReverseIterator;
		/// Const iterator used to iterate in reverse through active items.
		typedef typename ActiveSet::const_reverse_iterator ConstReverseIterator;

		/**
		 * Constructor. Initializes the pool with the specified maximum size.
		 * The size can only be changed when the pool is empty, so
		 * initialize the pool carefully.
		 * @param newMaxSize New maximum size for the pool.
		 * @see BaconBox::Pool<T>::droplets
		 */
		explicit Pool(SizeType newMaxSize) : droplets(newMaxSize),
			first(&(*droplets.begin())), actives() {
			// We initialize the droplets' pointers.
			init();
		}

		/**
		 * Gets an available item.
		 * @return Pointer to the first available item. It is not initialized
		 * yet.
		 */
		T *create() {
			// We make sure the pool is not completely used.
			if (first) {
				Droplet *newDroplet = first;
				first = newDroplet->next;

				actives.insert(&(newDroplet->value));

				return &(newDroplet->value);

			} else {
				return NULL;
			}
		}

		/**
		 * Makes the given item available in the pool. Make sure you free up all
		 * allocated memory the item uses before calling this function.
		 * Remember that you can call the destructor manually if it is what you
		 * need.
		 * @param toRemove Pointer to the item to be available again.
		 */
		void remove(T *toRemove) {
			if (!droplets.empty() && !actives.empty()) {
				Droplet *droplet = reinterpret_cast<Droplet *>(toRemove);

				// We make sure the droplet is from this pool.
				if (droplet >= &(*droplets.begin()) &&
				    droplet <= &(*(droplets.begin() + droplets.size() - 1))) {
					droplet->next = first;
					first = droplet;
					actives.erase(toRemove);
				}
			}
		}

		/**
		 * Checks whether or not this item is from the pool. It doesn't care if
		 * the item is available or not.
		 */
		bool isInPool(T *toCheck) {
			Droplet *droplet = reinterpret_cast<Droplet *>(toCheck);
			return !droplets.empty() && !actives.empty() && droplet >= &(*droplets.begin()) &&
			       droplet <= &(*(droplets.begin() + droplets.size() - 1));
		}

		/**
		 * Checks whether or not the item is active.
		 * @param toCheck Pointer to the item to check if it is active.
		 */
		bool isActive(T *toCheck) {
			return actives.find(toCheck) != actives.end();
		}

		/**
		 * Gets the number of items in use.
		 * @return Number of items in use and unavailable.
		 */
		SizeType getSize() const {
			return actives.size();
		}

		/**
		 * Checks if the pool is empty or not.
		 * @return True if all of the pool's items are available, false if not.
		 */
		bool isEmpty() const {
			return actives.empty();
		}

		/**
		 * Gets the maximum number of items the pool can use. Can be changed by
		 * resetting the pool.
		 * @return Maximum number of items the pool can use.
		 */
		SizeType getMaxSize() const {
			return droplets.size();
		}

		/**
		 * Resets the pool and makes all the items available again.
		 */
		void reset() {
			first = &(*droplets.begin());
			actives.clear();
			init();
		}

		/**
		 * Resets the pool, makes all the items available again and changes the
		 * maximum number of items the pool can have.
		 */
		void reset(SizeType newMaxSize) {
			droplets.resize(newMaxSize);
			reset();
		}

		/**
		 * Gets the iterator to the pointer of the first active item from the
		 * pool.
		 * @return Iterator to the pointer of the first active item from the
		 * pool.
		 */
		Iterator getBegin() {
			return actives.begin();
		}

		/**
		 * Gets the iterator to the pointer of the first active item from the
		 * pool.
		 * @return Iterator to the pointer of the first active item from the
		 * pool.
		 */
		ConstIterator getBegin() const {
			return actives.begin();
		}

		/**
		 * Gets an iterator to the element following the last pointer of the
		 * active items. This element acts as a placeholder, attempting to
		 * access it results in undefined behavior.
		 * @return Iterator to the element following the last pointer of the
		 * last active item.
		 */
		Iterator getEnd() {
			return actives.end();
		}

		/**
		 * Gets an iterator to the element following the last pointer of the
		 * active items. This element acts as a placeholder, attempting to
		 * access it results in undefined behavior.
		 * @return Iterator to the element following the last pointer of the
		 * last active item.
		 */
		ConstIterator getEnd() const {
			return actives.end();
		}

		/**
		 * Gets a reverse iterator to the first element of the reversed set of
		 * pointers to active items. It corresponds to the last element of the
		 * non-reversed set of pointers to active items.
		 * @return Reverse iterator to the pointer of the first active item.
		 */
		ReverseIterator getReverseBegin() {
			return actives.rbegin();
		}

		/**
		 * Gets a reverse iterator to the first element of the reversed set of
		 * pointers to active items. It corresponds to the last element of the
		 * non-reversed set of pointers to active items.
		 * @return Reverse iterator to the pointer of the first active item.
		 */
		ConstReverseIterator getReverseBegin() const {
			return actives.rbegin();
		}

		/**
		 * Gets a reverse iterator to the element following the last element of
		 * the reversed set of pointers to active items. It corresponds to the
		 * element preceding the first element of the non-reversed set of
		 * pointers to active items.
		 * @return Reverse iterator to the element following the pointer to the
		 * last active item.
		 */
		ReverseIterator getReverseEnd() {
			return actives.rend();
		}

		/**
		 * Gets a reverse iterator to the element following the last element of
		 * the reversed set of pointers to active items. It corresponds to the
		 * element preceding the first element of the non-reversed set of
		 * pointers to active items.
		 * @return Reverse iterator to the element following the pointer to the
		 * last active item.
		 */
		ConstReverseIterator getReverseEnd() const {
			return actives.rend();
		}
	private:
		/**
		 * Initializes the pool's droplets so they are all available and
		 * correctly point to the next available droplet.
		 */
		void init() {
			for (typename DropletVector::iterator i = droplets.begin(); i != droplets.end(); ++i) {
				if (i + 1 != droplets.end()) {
					i->next = &(*(i + 1));
				}
			}
		}

		/// Contains all the available and unavailable items.
		DropletVector droplets;

		/// Pointer to the first available droplet.
		Droplet *first;

		/// Contains pointers to all the active item in the pool.
		ActiveSet actives;
	};
}

#endif
