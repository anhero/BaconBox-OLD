/**
 * @file
 * @ingroup Display
 */
#ifndef RB_KEYABLE_H
#define RB_KEYABLE_H

namespace BaconBox {
	/**
	 * Represents an object that can be sorted in set/map with a member as its
	 * key in a body manager.
	 * @see BaconBox::BodyManager
	 * @see BaconBox::Manageable
	 */
	class Keyable {
		template <typename Key, typename Compare> friend class BodyManager;
		template <typename T, typename U> friend class SimpleBodyManager;
		template <typename T> friend class RenderBatchParent;
		template <typename T, bool ANIMATABLE> friend class RenderBatchMiddle;
	public:
		/**
		 * Default constructor.
		 */
		Keyable();

		/**
		 * Copy constructor.
		 * @param src Keyable to make a copy of.
		 */
		Keyable(const Keyable &src);

		/**
		 * Destructor.
		 */
		virtual ~Keyable();

		/**
		 * Assignment operator.
		 * @param src Keyable to make a copy of.
		 * @return Reference to the modified Keyable.
		 */
		Keyable &operator=(const Keyable &src);

		/**
		 * Checks if the Keyable body has had its key changed since its
		 * manager's last update.
		 * @return True if the key has changed, false if not.
		 * @see BaconBox::Keyable::keyChanged
		 */
		bool isKeyChanged() const;
	protected:
		/**
		 * Sets the keyChanged flag to true.
		 * @see BaconBox::Keyable::keyChanged
		 */
		void keyChange();
	private:
		/// Used by the body's manager to check if the body's key has changed.
		bool keyChanged;

		/**
		 * Sets the keyChanged flag to false. Used by the body's manager.
		 * @see BaconBox::Keyable::keyChanged
		 */
		void resetKeyChanged();
	};
}

#endif
