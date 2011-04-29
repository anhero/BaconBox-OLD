/**
 * @file
 */

#ifndef RB_COLLISIONDATA_H
#define RB_COLLISIONDATA_H

#include "Renderable.h"
#include "Side.h"

namespace RedBox{
	/** 
	 * This structure is used to return collision data 
     */
	struct CollisionData{
		///Side of the collision on object 1
		Side sideObj1;
		///Side of the collision on object 2
		Side sideObj2;
		///Overlapping amount 
		float overlap;
		///First colliding object
		Renderable * obj1;
		///Second colliding object
		Renderable * obj2;
	};
}

#endif
