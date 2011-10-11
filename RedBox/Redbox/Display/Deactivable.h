/**
 * @file
 */
#ifndef RB_DEACTIVABLE_H
#define RB_DEACTIVABLE_H

#include "Updateable.h"

namespace RedBox {
	class Deactivable : virtual public Updateable {
	public:
		/**
		 * Default constructor.
		 */
		Deactivable();

		/**
		 * Copy constructor.
		 * @param src Deactivable to make a copy of.
		 */
		Deactivable(const Deactivable &src);

		/**
		 * Destructor.
		 */
		virtual ~Deactivable();

		/**
		 * Assignment operator overload.
		 * @param src Deactivable to make a copy of.
		 * @return Reference to the modified Deactivable.
		 */
		Deactivable &operator=(const Deactivable &src);

		/**
		 * Checks if the body is active.
		 * @return True if the body is active, false if not.
		 * @see RedBox::Deactivable::active
		 */
		bool isActive() const;

		/**
		 * Sets if the body is active or not.
		 * @param newActive Whether or not the body is to be active.
		 * @see RedBox::Deactivable::active
		 */
		void setActive(bool newActive);
	private:
		/**
		 * If set to true, the body is updated by its container (like a state).
		 * If set to false, the body won't be updated.
		 */
		bool active;
	};
}

#endif
