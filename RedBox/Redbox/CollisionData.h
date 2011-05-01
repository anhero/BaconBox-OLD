/**
 * @file
 */

#ifndef RB_COLLISIONDATA_H
#define RB_COLLISIONDATA_H

#include "Side.h"



namespace RedBox{
	
	class Renderable;
	/** 
	 * This structure is used to return collision data 
     */
	struct CollisionData{
		///Side of the collision on object 1
		RB_SIDE sideObj1;
		///Side of the collision on object 2
		RB_SIDE sideObj2;
		///Overlapping amount 
		float overlap;
		///First colliding object
		Renderable * obj1;
		///Second colliding object
		Renderable * obj2;
		///Constructor
		CollisionData():sideObj1(0), sideObj2(0), overlap(0), obj1(NULL), obj2(NULL){}
	};
}

#endif
