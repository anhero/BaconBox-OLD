/**
 * @file
 * @ingroup Physics
 */
#ifndef RB_COLLISION_DETAILS_H
#define RB_COLLISION_DETAILS_H

#include <cstdlib>

#include "BaconBox/Helper/FlagSet.h"
#include "BaconBox/Side.h"

namespace BaconBox {
	class Collidable;
	/**
	 * Contains the details about a collision between two collidables.
	 * @ingroup Physics
	 */
	struct CollisionDetails {
		/// Number of pixels overlapping.
		float overlap;

		/// Pointer to the first concerned body.
		Collidable *body1;

		/// Pointer to the second concerned body.
		Collidable *body2;

		/// First body's sides that are colliding.
		FlagSet<Side> sidesBody1;

		/// Second body's sides that are colliding.
		FlagSet<Side> sidesBody2;

		/**
		 * Default constructor.
		 */
		CollisionDetails();

		/**
		 * Copy constructor.
		 * @param src CollisionDetails to make a copy of.
		 */
		CollisionDetails(const CollisionDetails &src);

		/**
		* Assignment operator.
		* @param src CollisionDetails to make a copy of.
		* @return Reference to the modified CollisionDetails.
		*/
		CollisionDetails &operator=(const CollisionDetails &src);
	};

}

#endif
