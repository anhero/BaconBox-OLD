/**
 * @file
 */
#ifndef RB_SIMPLE_BODY_MANAGER_H
#define RB_SIMPLE_BODY_MANAGER_H

#include <list>
#include <iterator>

namespace RedBox {
	/**
	 * Represents a simple body manager. A lot like BodyManager, but the order
	 * of update/render is determined by the order of insertion.
	 * @tparam T Type to contain.
	 * @see RedBox::BodyManager
	 */
	template <typename T>
	class SimpleBodyManager {
	public:
		/// Type that contains the bodies.
		typedef std::list<T *> Container;

		/// Type that represents a body.
		typedef T ValueType;

		/// Reference to a body.
		typedef T &Reference;

		/// Const reference to a body.
		typedef const T &ConstReference;

		/// Pointer to a body.
		typedef T *Pointer;

		/// Const pointer to a body.
		typedef const T *ConstPointer;

		/// Type used to count the number of bodies.
		typedef typename Container::size_type SizeType;

		/**
		 * Iterator to iterate through the bodies.
		 */
		class Iterator {
			friend class SimpleBodyManager<ValueType>;
		public:
			Iterator() {}
			Iterator(const Iterator &src) : it(src.it) {}

			Iterator &operator=(const Iterator &src) {
				it = src.it;
				return *this;
			}

			bool operator==(const Iterator &other) const {
				return it == other.it;
			}

			bool operator!=(const Iterator &other) const {
				return it != other.it;
			}

			Iterator &operator++() {
				++it;
				return *this;
			}

			Iterator operator++(int) {
				Iterator result(*this);
				++it;
				return result;
			}

			Iterator &operator--() {
				--it;
				return *this;
			}

			Iterator operator--(int) {
				Iterator result(*this);
				--it;
				return result;
			}

			Reference operator*() const {
				return *(*it);
			}

			Pointer operator->() const {
				return *it;
			}
		private:
			explicit Iterator(typename Container::iterator newIt) : it(newIt) {}
			typename Container::iterator it;
		};

		/**
		 * Const iterator to iterate through the bodies.
		 */
		class ConstIterator {
			friend class SimpleBodyManager<ValueType>;
		public:
			ConstIterator() {}
			ConstIterator(const ConstIterator &src) : it(src.it) {}

			ConstIterator &operator=(const ConstIterator &src) {
				it = src.it;
				return *this;
			}

			bool operator==(const ConstIterator &other) const {
				return it == other.it;
			}

			bool operator!=(const ConstIterator &other) const {
				return it != other.it;
			}

			ConstIterator &operator++() {
				++it;
				return *this;
			}

			ConstIterator operator++(int) {
				ConstIterator result(*this);
				++it;
				return result;
			}

			ConstIterator &operator--() {
				--it;
				return *this;
			}

			ConstIterator operator--(int) {
				ConstIterator result(*this);
				--it;
				return result;
			}

			ConstReference operator*() const {
				return *(*it);
			}

			ConstPointer operator->() const {
				return *it;
			}
		private:
			explicit ConstIterator(typename Container::const_iterator newIt) : it(newIt) {}
			typename Container::const_iterator it;
		};

		/// Reverse iterator.
		typedef std::reverse_iterator<Iterator> ReverseIterator;

		/// Const reverse iterator.
		typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

		/**
		 * Default constructor.
		 */
		SimpleBodyManager() {
		}

		/**
		 * Copy constructor.
		 * @param src Simple body manager to make a copy of.
		 */
		SimpleBodyManager(const SimpleBodyManager<ValueType> &src) {
			add(src);
		}

		/**
		 * Destructor.
		 */
		~SimpleBodyManager() {
			free();
		}

		/**
		 * Assignment operator overload.
		 * @param src Simple body manager to copy.
		 * @return Reference to modified instance.
		 */
		SimpleBodyManager<ValueType> &operator=(const SimpleBodyManager<ValueType> &src) {
			if (this != &src) {
				clear();
				add(src);
			}

			return *this;
		}

		/**
		 * Adds a new body to the body manager.
		 * @param newBody New body to add to the body manager. Must neither be
		 * NULL nor already managed by a body manager.
		 */
		void add(Pointer newBody) {
			if (newBody && !newBody->isManaged()) {
				newBody->setManaged(true);
				bodies.push_back(newBody);
			}
		}

		/**
		 * Adds duplicates of another body manager's bodies.
		 * @param newBodies Bodies to clone and add to the instance.
		 */
		void add(const SimpleBodyManager<ValueType> &newBodies) {
			for (ConstIterator i = newBodies.getBegin(); i != newBodies.getEnd(); ++i) {
				add(i->clone());
			}
		}

		/**
		 * Updates the active and enabled bodies.
		 */
		void update() {
			typename Container::iterator i = bodies.begin();

			// We loop through each body.
			while (i != bodies.end()) {
				// We check if it needs to be deleted.
				if ((*i)->isToBeDeleted()) {
					toDelete.push_back(*i);
					bodies.erase(i++);

				} else {
					// We only update if enabled or active.
					if ((*i)->isEnabled() && (*i)->isActive()) {
						(*i)->update();
					}

					++i;
				}
			}

			// We delete the bodies that need to be deleted.
			for (i = toDelete.begin(); i != toDelete.end(); ++i) {
				delete *i;
			}

			toDelete.clear();
		}

		/**
		 * Gets an iterator to the first body.
		 * @return Iterator to the first body.
		 */
		Iterator getBegin() {
			return Iterator(bodies.begin());
		}

		/**
		 * Gets an iterator to the first body.
		 * @return Iterator to the first body.
		 */
		ConstIterator getBegin() const {
			return ConstIterator(bodies.begin());
		}

		/**
		 * Gets an iterator to the body following the last body. Acts as a
		 * placeholder, attempting to access it results in undefined behavior.
		 * @return Iterator to the body following the last body.
		 */
		Iterator getEnd() {
			return Iterator(bodies.end());
		}

		/**
		 * Gets an iterator to the body following the last body. Acts as a
		 * placeholder, attempting to access it results in undefined behavior.
		 * @return Iterator to the body following the last body.
		 */
		ConstIterator getEnd() const {
			return ConstIterator(bodies.end());
		}

		/**
		 * Gets a reverse iterator to the first body of the reversed simple body
		 * manager. It corresponds to the last element of the non-reversed
		 * simple body manager.
		 * @return Reverse iterator to the first body.
		 */
		ReverseIterator getReverseBegin() {
			return ReverseIterator(Iterator(bodies.end()));
		}

		/**
		 * Gets a reverse iterator to the first body of the reversed simple body
		 * manager. It corresponds to the last element of the non-reversed
		 * simple body manager.
		 * @return Reverse iterator to the first body.
		 */
		ConstReverseIterator getReverseBegin() const {
			return ConstReverseIterator(ConstIterator(bodies.end()));
		}

		/**
		 * Gets a reverse iterator to the body following the last body of the
		 * reversed simple body manager. It corresponds to the body preceding
		 * the first body of the non-reversed simple body manager. This body
		 * acts as a placeholder, attempting to access it results in undefined
		 * behavior.
		 * @return Reverse iterator to the body following the last body.
		 */
		ReverseIterator getReverseEnd() {
			return ReverseIterator(Iterator(bodies.begin()));
		}

		/**
		 * Gets a reverse iterator to the body following the last body of the
		 * reversed simple body manager. It corresponds to the body preceding
		 * the first body of the non-reversed simple body manager. This body
		 * acts as a placeholder, attempting to access it results in undefined
		 * behavior.
		 * @return Reverse iterator to the body following the last body.
		 */
		ConstReverseIterator getReverseEnd() const {
			return ConstReverseIterator(ConstIterator(bodies.begin()));
		}

		/**
		 * Gets the number of bodies the manager currently manages.
		 * @return Number of bodies managed.
		 */
		SizeType getNbBodies() const {
			return bodies.size();
		}

		/**
		 * Checks wether or not the manager contains bodies.
		 * @return True if the manager contains bodies, false if not.
		 */
		bool isEmpty() const {
			return bodies.empty();
		}

		/**
		 * Removes all bodies from the body manager.
		 */
		void clear() {
			free();
			bodies.clear();
			toDelete.clear();
		}
	private:
		/// Bodies to be managed.
		Container bodies;

		/// Bodies to be deleted at the end of the next update call.
		Container toDelete;

		/**
		 * Deletes all of the bodies.
		 */
		void free() {
			for (typename Container::iterator i = bodies.begin(); i != bodies.end();
			     ++i) {
				delete *i;
			}

			for (typename Container::iterator i = toDelete.begin(); i != toDelete.end();
			     ++i) {
				delete *i;
			}
		}
	};
}

#endif