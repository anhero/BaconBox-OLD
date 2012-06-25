/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SIMPLE_MANAGEABLE_H
#define RB_SIMPLE_MANAGEABLE_H

#include "Disableable.h"
#include "Manageable.h"

namespace BaconBox {
	/**
	 * Class that represents the minimum requirements for a body managed
	 * by SimpleBodyManager.
	 * @see BaconBox::SimpleBodyManager
	 * @ingroup Display
	 */
	class SimpleManageable : public Disableable, public Manageable {
	public:
		/**
		 * Default constructor.
		 */
		SimpleManageable();
		
		/**
		 * Copy constructor.
		 * @param src Simple manageable to make a copy of.
		 */
		SimpleManageable(const SimpleManageable &src);
		
		/**
		 * Destructor.
		 */
		virtual ~SimpleManageable();
		
		/**
		 * Assignment operator overload.
		 * @param src Simple manageable to copy.
		 * @return Reference to the modified instance.
		 */
		SimpleManageable &operator=(const SimpleManageable &src);
	};
}

#endif