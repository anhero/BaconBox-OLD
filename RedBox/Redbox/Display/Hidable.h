/**
 * @file
 * @ingroup Display
 */
#ifndef RB_HIDABLE_H
#define RB_HIDABLE_H

#include "Maskable.h"

namespace RedBox {
	/**
	 * Represents a body that can be rendered and has a flag to set whether the
	 * body is visible or not.
	 * @ingroup Display
	 */
	class Hidable : virtual public Maskable {
	public:
		/**
		 * Default constructor.
		 */
		Hidable();

		/**
		 * Copy constructor.
		 * @param src Hidable to make a copy of.
		 */
		Hidable(const Hidable &src);

		/**
		 * Destructor.
		 */
		virtual ~Hidable();

		/**
		 * Assignment operator.
		 * @param src Hidable to make a copy of.
		 * @return Reference to the modified Hidable.
		 */
		Hidable &operator=(const Hidable &src);

		/**
		 * Checks if the body is visible.
		 * @return True if the body is visible, false if not.
		 * @see RedBox::Deactivable::active
		 */
		bool isVisible() const;

		/**
		 * Sets the body's visibility.
		 * @param newVisible Whether or not the body is to be visible.
		 * @see RedBox::Hidable::visible
		 */
		void setVisible(bool newVisible);
	private:
		/**
		 * If set to true, the body is rendered by its container (like a state).
		 * If set to false, the body won't be rendered.
		 */
		bool visible;
	};

}

#endif
