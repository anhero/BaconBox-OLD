/**
 * @file
 * @ingroup Display
 */
#ifndef RB_MANAGEABLE_BY_KEY_H
#define RB_MANAGEABLE_BY_KEY_H

#include "BaconBox/Display/Manageable.h"
#include "BaconBox/Display/Keyable.h"

namespace BaconBox {
	/**
	 * Represents an object that is manageable by key in a body manager.
	 * @see BaconBox::BodyManager
	 */
	class ManageableByKey : public Keyable, public Manageable {
	public:
		/**
		 * Default constructor.
		 */
		ManageableByKey();

		/**
		 * Copy constructor.
		 * @param src ManageableByKey to make a copy of.
		 */
		ManageableByKey(const ManageableByKey &src);

		/**
		 * Destructor.
		 */
		virtual ~ManageableByKey();

		/**
		 * Assignment operator overload.
		 * @param src ManageableByKey to copy.
		 * @return Reference to the modified instance.
		 */
		ManageableByKey &operator=(const ManageableByKey &src);
	protected:
		using Keyable::keyChange;
	};

}

#endif
