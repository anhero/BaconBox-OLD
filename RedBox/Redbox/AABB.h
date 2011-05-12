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
		 * @param newMinX Left side's coordinate.
		 * @param newMaxX Right side's coordinate.
		 * @param newMinY Top side's coordinate.
		 * @param newMaxY Bottom side's coordinate.
		 */
		AABB(float newMinX, float newMaxX, float newMinY, float newMaxY);

		/**
		 * Copy constructor.
		 * @param src AABB to make a copy of.
		 */
		AABB(const AABB& src);

		/**
		 * Assignation operator overload.
		 * @param src AABB to make a copy of.
		 * @return Reference to the modified AABB.
		 */
		AABB& operator=(const AABB& src);

		/**
		 * Checks if the AABB overlaps with another AABB.
		 * @param rect Other AABB to check the overlapping with.
		 * @return True if the rectangle (AABB) is intersecting the current
		 * AABB, fase if not.
		 */
		bool overlaps(const AABB& rect) const;

		/**
		 * Checks if a point is inside the AABB.
		 * @param point Point to check for if it overlaps with the AABB.
		 * @return True if the point is inside the AABB, false if not.
		 */
		bool overlaps(const Vec2& point) const;

		/**
		 * Checks if a point is inside the AABB.
		 * @param x Horizontal coordinate of the point to check overlapping
		 * with.
		 * @param y Vertical coordinate of the point to check overlapping with.
		 * @return True if the point is inside the AABB, false if not.
		 */
		bool overlaps(float x, float y) const;
		
		/**
		 * Return true if the current AABB overlaps the given  horizontal line.
		 * The line must be a flat line parallel to the X axis (cutting the Y
		 * axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the Y axis. If the line
		 * has no boundaries, it will cut the Y axis at this position.
		 * @param lowerXBoundary Lower boundary of the line (a AABB with a maxX
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherXBoundary, the line is infinite.
		 * @param higherXBoundary Higher boundary of the line (a AABB with a
		 * minX higher than this value won't collide with the line). If the
		 * value is lower than lowerXBoundary, the line is infinite.
		 * @return True if the AABB and the horizontal line overlap, false if
		 * not.
		 */
		bool horizLineOverlaps(float linePosition, float lowerXBoundary = 1.0f,
							   float higherXBoundary = -1.0f);

		/**
		 * Return true if the current AABB overlaps the given vertical line. The
		 * line must be a flat line parallel to the Y axis (cutting the X axis
		 * at position indicated by linePosition.
		 * @param linePosition Position of the line on the X axis. (If the line
		 * have no boundaries, it will cut the X axis at this position.
		 * @param lowerYBoundary Lower boundary of the line (a AABB with a maxY
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherYBoundary, the line is infinite.
		 * @param higherYBoundary Higher boundary of the line (a AABB with a
		 * minY higher than this value won't collide with the line). If the
		 * value is lower than lowerYBoundary, the line is infinite.
		 * @return True if the AABB and the vertical line overlap, false if not.
		 */
		bool vertLineOverlaps(float linePosition, float lowerYBoundary = 1.0f,
							  float higherYBoundary = -1.0f);

		/**
		 * Checks if two AABB are intersecting.
		 * @param rect1 First AABB to check for collisions with.
		 * @param rect2 Second AABB to check for collisions with.
		 * @return True if the two rectangles (AABB) are intersecting, false
		 * if not.
		 */
		static bool overlaps(const AABB& rect1, const AABB& rect2);

		/**
		 * Checks if a point overlaps with an AABB.
		 * @param x Point's horizontal coordinate.
		 * @param y Point's vertical coordinate.
		 * @param rect AABB used to check for overlapping.
		 * @return True if the point and the AABB overlap, false if not.
		 */
		static bool overlaps(float x, float y, const AABB& rect);

		/**
		 * Checks if a point overlaps with an AABB.
		 * @param point Point used to check for overlapping.
		 * @param rect AABB used to check for overlapping.
		 * @return True if the point and the AABB overlap, false if not.
		 */
		static bool overlaps(const Vec2& point, const AABB& rect);
		
		/**
		 * Return true if the given AABB overlaps the given horizontal line. The
		 * line must be a flat line parallel to the X axis (cutting the Y axis
		 * at position indicated by linePosition.
		 * @param rect The AABB you want to test.
		 * @param linePosition Position of the line on the Y axis. (If the line
		 * has no boundaries, it will cut the Y axis at this position.
		 * @param lowerXBoundary Lower boundary of the line (a AABB with a maxX
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherXBoundary, the line is infinite.
		 * @param higherXBoundary Higher boundary of the line (a AABB with a
		 * minX higher than this value won't collide with the line). If the
		 * value is lower than lowerXBoundary, the line is infinite.
		 * @return True if the AABB and the horizontal line overlap, false if
		 * not.
		 */
		static bool horizLineOverlaps(AABB & rect, float linePosition,
									  float lowerXBoundary = 1.0f,
									  float higherXBoundary = -1.0f);
		
		/**
		 * Return true if the given AABB overlaps the given vertical line. The
		 * line must be a flat line parallel to the Y axis (cutting the X axis
		 * at position indicated by linePosition.
		 * @param rect The AABB you want to test.
		 * @param linePosition Position of the line on the X axis. (If the line
		 * has no boundaries, it will cut the X axis at this position.
		 * @param lowerYBoundary Lower boundary of the line (a AABB with a maxY
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherYBoundary, the line is infinite.
		 * @param higherYBoundary Higher boundary of the line (a AABB with a
		 * minY higher than this value won't collide with the line). If the
		 * value is lower than lowerYBoundary, the line is infinite.
		 * @return True if the AABB and the vertical line overla, false if not.
		 */
		static bool vertLineOverlaps(AABB & rect, float linePosition,
									 float lowerYBoundary = 1.0f,
									 float higherYBoundary = -1.0f);
	private:
		/// Left side's coordinate.
		float minX;

		/// Right side's coordinate.
		float maxX;

		/// Top side's coordinate.
		float minY;

		/// Bottom side's coordinate.
		float maxY;
	};
}

#endif
