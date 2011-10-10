/**
 * @file
 */
#ifndef RB_BODY_MANAGER_H
#define RB_BODY_MANAGER_H

#include <set>
#include <list>
#include <cassert>
#include <algorithm>

#include "DeleteHelper.h"
#include "Manageable.h"
#include "Disableable.h"
#include "StaticAssert.h"
#include "IsBaseOf.h"
#include "Console.h"

namespace RedBox {

	/**
	 * Represents a body manager. It manages bodies that can be ordered using
	 * a value that is an attribute of the body.
	 * @tparam Key Type of body the manager contains. Must be derived from
	 * Manageable and Disableable.
	 * @tparam Compare Comparator used to compare the body's attribute used for
	 * ordering.
	 */
	template <typename Key, typename Compare>
	class BodyManager {
	public:
		typedef Key KeyType;
		typedef Key ValueType;
		typedef Compare KeyCompare;
		typedef Compare ValueCompare;

		/**
		 * Default constructor.
		 */
		BodyManager() {
		}

		/**
		 * Copy constructor.
		 * @param src BodyManager to make a copy of.
		 */
		BodyManager(const BodyManager<Key, Compare> &src) {
			copyFrom(src);
		}

		/**
		 * Destructor.
		 */
		virtual ~BodyManager() {
			clearBodies();
		}

		/**
		 * Assignment operator.
		 * @param src BodyManager to make a copy of.
		 * @return Reference to the modified BodyManager.
		 */
		BodyManager<Key, Compare> &operator=(const BodyManager<Key, Compare> &src) {
			if (this != &src) {
				clearBodies();
				toAdd.clear();
				toDelete.clear();
				keyChange.clear();
				bodies.clear();
				copyFrom(src);
			}

			return *this;
		}

		/**
		 * Internal update method called when the manager needs to be updated.
		 */
		virtual void internalUpdate() {
			// We add the bodies to the BodyMap.
			std::for_each(toAdd.begin(), toAdd.end(), std::bind1st(std::mem_fun(&BodyManager<Key, Compare>::addDirect), this));
			// We clear the temporary list of bodies to add.
			toAdd.clear();

			// We update the bodies.
			typename BodyMap::iterator i = bodies.begin();

			while (i != bodies.end()) {
				// We check if the delete flag is on.
				if ((*i)->isToBeDeleted()) {
					// We put the body in the list of bodies to delete.
					toDelete.push_back(*i);
					// We remove the body from the BodyMap.
					bodies.erase(i++);

				} else {
					if ((*i)->isEnabled() && (*i)->isActive()) {
						// We update the body.
						(*i)->update();

						// We check if the key has changed.
						if ((*i)->isKeyChanged()) {
							// If so, we put it at the right layer in the
							// BodyMap. To do that, we first put it in the list
							// of bodies that have had their key changed.
							keyChange.push_back((*i));
							// We remove it from the BodyMap.
							bodies.erase(i++);

						} else {
							++i;
						}

					} else {
						++i;
					}
				}
			}

			// We delete all the bodies from the list of GraphicBodys that need
			// to be deleted.
			std::for_each(toDelete.begin(), toDelete.end(), DeletePointer());
			// We clear the list.
			toDelete.clear();

			// Put the bodies which have had their key changed back into the
			// BodyMap.
			for (typename BodyList::iterator i = keyChange.begin(); i != keyChange.end();
			     ++i) {
				addDirect(*i);
			}

			keyChange.clear();
		}

		/**
		 * Internal render method called when the manager needs to be rendered.
		 */
		virtual void internalRender() = 0;

		/**
		 * Adds a body to the manager. The manager will take care of memory
		 * freeing.
		 * @param newBody Pointer to the body to add to the manager.
		 * @see RedBox::BodyManager::toAdd
		 * @see RedBox::BodyManager::bodies
		 */
		void add(KeyType *newBody) {
			if (newBody) {
				if (!newBody->isManaged()) {
					newBody->setManaged(true);
					toAdd.push_front(newBody);

				} else {
					Console::println("Tried to add a body that is already in a body manager.");
				}

			} else {
				Console::println("Tried to add an invalid body (" + Console::toString(newBody) + ") to the body manager.");
			}
		}

	protected:
		/// Represents the container's type to use to store the managed bodies.
		typedef std::multiset<KeyType *, KeyCompare> BodyMap;

		/// Stores all the bodies that need to be updated and rendered.
		BodyMap bodies;
	private:
		/// Makes sure the body type is derived from the Manageable class.
		typedef typename StaticAssert<IsBaseOf<Manageable, KeyType>::RESULT>::Result IsManageable;

		/// Makes sure the body type is derived from the Disableable class.
		typedef typename StaticAssert<IsBaseOf<Disableable, KeyType>::RESULT>::Result IsDisableable;

		/// Represents the container's type to temporarily store bodies in a list.
		typedef std::list<KeyType *> BodyList;

		/// Temporarily stores the bodies to be deleted.
		BodyList toDelete;

		/// Temporarily stores the bodies to be added.
		BodyList toAdd;

		/// Temporarily stores the bodies that have had their key changed.
		BodyList keyChange;

		/**
		 * Directly adds a body in the BodyMap. It will then be able to be
		 * updated and rendered correctly.
		 * @param newBody Pointer to the body to add.
		 */
		void addDirect(KeyType *newBody) {
			assert(newBody && newBody->isManaged());

			newBody->resetKeyChanged();
			bodies.insert(newBody);
		}

		/**
		 * Frees all memory used by the body manager.
		 */
		void clearBodies() {
			// We delete all the bodies from the list of bodies that need to be
			// deleted.
			std::for_each(toDelete.begin(), toDelete.end(), DeletePointer());

			// We delete the bodies that were waiting to be added.
			std::for_each(toAdd.begin(), toAdd.end(), DeletePointer());

			// We delete the bodies that had their key changed.
			std::for_each(keyChange.begin(), keyChange.end(), DeletePointer());

			// We delete the bodies.
			std::for_each(bodies.begin(), bodies.end(), DeletePointer());
		}

		/**
		 * Copies a body manager's bodies into the current body manager.
		 * @param src Body manager to make a copy of.
		 */
		void copyFrom(const BodyManager<Key, Compare> &src) {
			for (typename BodyList::const_iterator i = src.toDelete.begin();
			     i != src.toDelete.end(); ++i) {
				assert(*i);
				toDelete.insert(new KeyType(**i));
			}

			for (typename BodyList::const_iterator i = src.toAdd.begin();
			     i != src.toAdd.end(); ++i) {
				assert(*i);
				toAdd.insert(new KeyType(**i));
			}

			for (typename BodyList::const_iterator i = src.keyChange.begin();
			     i != src.keyChange.end(); ++i) {
				assert(*i);
				keyChange.insert(new KeyType(**i));
			}

			for (typename BodyMap::const_iterator i = src.bodies.begin();
			     i != src.bodies.end(); ++i) {
				assert(*i);
				bodies.insert(new KeyType(**i));
			}
		}
	};

}

#endif
