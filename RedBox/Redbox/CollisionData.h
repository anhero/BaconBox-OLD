/**
 * @file
 */

#ifndef RB_COLLISIONDATA_H
#define RB_COLLISIONDATA_H

#include "Side.h"



namespace RedBox{
	
	class GraphicBody;
	/** 
	 * This structure is used to return collision data 
     */
	struct CollisionData{
		/// Side of the collision on object 1
		Side::Enum sideObj1;
		/// Side of the collision on object 2
		Side::Enum sideObj2;
		/// Overlapping amount
		float overlap;
		/// First colliding object
		GraphicBody* obj1;
		///Second colliding object
		GraphicBody* obj2;
		/// Constructor
		CollisionData():sideObj1(0), sideObj2(0), overlap(0), obj1(NULL), obj2(NULL){}
	};
}

#endif
