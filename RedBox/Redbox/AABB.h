/**
 * @file
 */
#ifndef RB_AABB_H
#define RB_AABB_H

#include "Object.h"

#include "Vec2.h"

namespace RedBox {
	/**
	 * This class represent an axis aligned bounding box (AABB).
	 */
	class AABB : public Object {
	public:
		/**
		 * Default constructor.
		 */
		AABB();
		/**
		 * Parameterized constructor.
		 */
		AABB(float newMinX, float newMaxX, float newMinY, float newMaxY);

		/**
		 * Copy constructor.
		 * @param src AABB to make a copy of.
		 */
		AABB(const AABB& src);

		/**
		 * Assignation operator overload.
		 */
		AABB& operator=(const AABB& src);

		/// Return true if the rectangle (AABB) is intersecting the current AABB
		bool overlaps(const AABB& rect) const;

		/// Return true if the point is inside the current AABB.
		bool overlaps(const Vec2& point) const;

		/// Return true if the point is inside the current AABB.
		bool overlaps(float x, float y) const;
		
		
		/**
		 * Return true if the current AABB overlaps the given line. The line must be a flat 
		 * line parallel to the X axis (cutting the Y axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the Y axis. (If the line have no boundaries, 
		 * it will cut the Y axis at this position.
		 * @param lowerXboundary Lower boundary of the line (a AABB with a maxX lower than 
		 * this value won't collide with the line). If the value is higher than higherXBoundary, the line is infinite.
		 * @param higherXboundary Higher boundary of the line (a AABB with a minX higher than 
		 * this value won't collide with the line). If the value is lower than lowerXBoundary, the line is infinite.
		 */
		bool lineXOverlaps(float linePosition, float lowerXBoundary = 1.0f, float higherXBoundary = -1.0f);
		/**
		 * Return true if the current AABB overlaps the given line. The line must be a flat 
		 * line parallel to the Y axis (cutting the X axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the X axis. (If the line have no boundaries, 
		 * it will cut the X axis at this position.
		 * @param lowerYboundary Lower boundary of the line (a AABB with a maxY lower than 
		 * this value won't collide with the line). If the value is higher than higherYBoundary, the line is infinite.
		 * @param higherYboundary Higher boundary of the line (a AABB with a minY higher than 
		 * this value won't collide with the line). If the value is lower than lowerYBoundary, the line is infinite.
		 */
		bool lineYOverlaps(float linePosition, float lowerYBoundary = 1.0f, float higherYBoundary = -1.0f);


		/// Return true if the two rectangle (AABB) are intersecting
		static bool overlaps(const AABB& rect1, const AABB& rect2);

		/// Return true if the point is inside the given rectangle.
		static bool overlaps(float x, float y, const AABB& rect);

		/// Return true if the point is inside the given rectangle.
		static bool overlaps(const Vec2& point, const AABB& rect);
		
		
		/**
		 * Return true if the given AABB overlaps the given line. The line must be a flat 
		 * line parallel to the X axis (cutting the Y axis at position indicated by linePosition.
		 * @param rect The AABB you want to test.
		 * @param linePosition Position of the line on the Y axis. (If the line have no boundaries, 
		 * it will cut the Y axis at this position.
		 * @param lowerXboundary Lower boundary of the line (a AABB with a maxX lower than 
		 * this value won't collide with the line). If the value is higher than higherXBoundary, the line is infinite.
		 * @param higherXboundary Higher boundary of the line (a AABB with a minX higher than 
		 * this value won't collide with the line). If the value is lower than lowerXBoundary, the line is infinite.
		 */
		static bool lineXOverlaps(AABB & rect, float linePosition, float lowerXBoundary = 1.0f, float higherXBoundary = -1.0f);
		
		/**
		 * Return true if the given AABB overlaps the given line. The line must be a flat 
		 * line parallel to the Y axis (cutting the X axis at position indicated by linePosition.
		 * @param rect The AABB you want to test.
		 * @param linePosition Position of the line on the X axis. (If the line have no boundaries, 
		 * it will cut the X axis at this position.
		 * @param lowerYboundary Lower boundary of the line (a AABB with a maxY lower than 
		 * this value won't collide with the line). If the value is higher than higherYBoundary, the line is infinite.
		 * @param higherYboundary Higher boundary of the line (a AABB with a minY higher than 
		 * this value won't collide with the line). If the value is lower than lowerYBoundary, the line is infinite.
		 */
		static bool lineYOverlaps(AABB & rect, float linePosition, float lowerYBoundary = 1.0f, float higherYBoundary = -1.0f);
		

	private:
		float minX;
		float maxX;
		float minY;
		float maxY;
	};
}

#endif
