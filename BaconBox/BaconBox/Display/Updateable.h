/**
 * @file
 */
#ifndef RB_UPDATEABLE_INTERFACE_H
#define RB_UPDATEABLE_INTERFACE_H

namespace BaconBox {
	/**
	 * Interface used for all updateable bodies.
	 */
	class Updateable {
	public:
		/**
		 * Destructor.
		 */
		virtual ~Updateable();

		/**
		 * Updates the body.
		 */
		virtual void update() = 0;
	};
}

#endif
