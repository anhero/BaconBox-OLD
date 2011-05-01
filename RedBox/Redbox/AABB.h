/**
 * @file
 */

#ifndef RB_FILE_H
#define RB_FILE_H

namespace RedBox{
	/** 
	 * This class represent an axis aligned bounding box (AABB)
     */
	class AABB{
	public:
		float minX;
		float maxX;
		float minY;
		float maxY;
		
		///Constructor
		AABB(float minX, float maxX, float minY, float maxY);
		
		///Return true if the rectangle (AABB) is intersecting the current AABB
		bool overlaps(AABB * rect);
		
		///Return true if the two rectangle (AABB) are intersecting
		static bool overlaps(AABB * rect1, AABB * rect2);
	};
}

#endif
