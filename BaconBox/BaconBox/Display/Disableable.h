/**
 * @file
 * @ingroup Display
 */
#ifndef RB_DISABLEABLE_H
#define RB_DISABLEABLE_H

#include "Deactivable.h"
#include "Hidable.h"

namespace BaconBox {
	/**
	 * Represents a body that can be disabled, thus ignoring whether or not it
	 * is active and/or visible. Once disabled, it is neither active nor
	 * visible, but it will retain its active and visible flags once re-enabled.
	 * @ingroup Display
	 */
	class Disableable : public Deactivable, public Hidable {
	public:
		/**
		 * Default constructor.
		 */
		Disableable();

		/**
		 * Copy constructor.
		 * @param src Disableable to make a copy of.
		 */
		Disableable(const Disableable &src);

		/**
		 * Destructor.
		 */
		virtual ~Disableable();

		/**
		 * Assignment operator.
		 * @param src Disableable to make a copy of.
		 * @return Reference to the modified Disableable.
		 */
		Disableable &operator=(const Disableable &src);

		/**
		 * Checks if the body is enabled. A disabled body will neither be
		 * updated nor rendered.
		 * @return True if the body is enabled, false if not.
		 * @see BaconBox::Disableable::enabled
		 */
		bool isEnabled() const;

		/**
		 * Sets if the body is enabled or not. A disabled body will neither be
		 * updated nor rendered.
		 * @param newEnabled New value for the enabled flag.
		 * @see BaconBox::Disableable::enabled
		 */
		void setEnabled(bool newEnabled);
	private:
		/**
		 * If set to true, the body is updated (only if the body is also active)
		 * and rendered (only if the body is also visible). If set to false, the
		 * body will neither be updated nor rendered, regardless if it's active
		 * or not and visible or not.
		 */
		bool enabled;
	};

}

#endif
