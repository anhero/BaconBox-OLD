/**
 * @file
 */

#ifndef RB_AABB_H
#define RB_AABB_H

#include "Vec2.h"

namespace RedBox {
	/** 
	 * This class represent an axis aligned bounding box (AABB)
     */
	class AABB{
	public:
		float minX;
		float maxX;
		float minY;
		float maxY;
		
		/// Default constructor
		AABB(float newMinX, float newMaxX, float newMinY, float newMaxY);
		
		/// Return true if the rectangle (AABB) is intersecting the current AABB
		bool overlaps(const AABB& rect) const;

		/// Return true if the point is inside the current AABB.
		bool overlaps(const Vec2& point) const;

		/// Return true if the point is inside the current AABB.
		bool overlaps(float x, float y) const;

		/// Return true if the two rectangle (AABB) are intersecting
		static bool overlaps(const AABB& rect1, const AABB& rect2);

		/// Return true if the point is inside the given rectangle.
		static bool overlaps(float x, float y, const AABB& rect);

		/// Return true if the point is inside the given rectangle.
		static bool overlaps(const Vec2& point, const AABB& rect);
	};
}

#endif