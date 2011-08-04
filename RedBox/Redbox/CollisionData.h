/**
 * @file
 */

#ifndef RB_COLLISIONDATA_H
#define RB_COLLISIONDATA_H

#include "Side.h"



namespace RedBox{
	
	class GraphicBody;
	/** 
	 * This structure is used to return collision data.
     */
	struct CollisionData{
		/// Side of the collision on object 1
		Side sideObj1;
		/// Side of the collision on object 2
		Side sideObj2;
		/// Overlapping amount
		float overlap;
		/// First colliding object
		GraphicBody* obj1;
		/// Second colliding object
		GraphicBody* obj2;
		/**
		 * Default constructor.
		 */
		CollisionData() : sideObj1(Side::LEFT), sideObj2(Side::RIGHT),
			overlap(0), obj1(NULL), obj2(NULL) {
		}
	};
}

#endif
