/**
 * @file
 * @ingroup Display
 */
#ifndef RB_MANAGEABLE_H
#define RB_MANAGEABLE_H

namespace BaconBox {
	/**
	 * Represents a manageable body. All classes that can be managed by a body
	 * manager will be derived from this class.
	 * @ingroup Display
	 */
	class Manageable {
		template <typename Key, typename Compare> friend class BodyManager;
		template <typename T, typename U> friend class SimpleBodyManager;
		template <typename T> friend class RenderBatchParent;
		template <typename T, bool ANIMATABLE> friend class RenderBatchMiddle;
	public:
		/**
		 * Default constructor.
		 */
		Manageable();

		/**
		 * Copy constructor.
		 * @param src Manageable to make a copy of.
		 */
		Manageable(const Manageable &src);

		/**
		 * Destructor.
		 */
		virtual ~Manageable();

		/**
		 * Assignment operator.
		 * @param src Manageable to make a copy of.
		 * @return Reference to the modified Manageable.
		 */
		Manageable &operator=(const Manageable &src);

		/**
		 * Checks if the body is currently being managed by a manager.
		 * @return True if the body is currently being managed, false if not.
		 * @see BaconBox::Manageable::managed
		 */
		bool isManaged() const;

		/**
		 * Checks if the body needs to be deleted from its manager.
		 * @return True if the body needs to be deleted, false if not.
		 * @see BaconBox::Manageable::toBeDeleted
		 */
		bool isToBeDeleted() const;

		/**
		 * Sets whether the body is to be deleted or not.
		 * @param newToBeDeleted New boolean value for the "to be deleted" flag.
		 * @see BaconBox::Manageable::toBeDeleted
		 */
		void setToBeDeleted(bool newToBeDeleted);
	private:
		/**
		 * Used by the body's manager to make sure the body cannot be managed by
		 * two body managers.
		 */
		bool managed;

		/**
		 * Used to know if the body needs to be deleted by its manager. Used
		 * by the body's manager.
		 */
		bool toBeDeleted;

		/**
		 * Sets whether or not the body is currently managed by a body manager.
		 * Used by the body's manager.
		 * @see BaconBox::Manageable::managed
		 */
		void setManaged(bool newManaged);
	};

}

#endif
