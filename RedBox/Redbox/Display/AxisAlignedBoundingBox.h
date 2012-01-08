/**
 * @file
 * @ingroup Physics
 */
#ifndef RB_AXIS_ALIGNED_BOUNDING_BOX_H
#define RB_AXIS_ALIGNED_BOUNDING_BOX_H

#include "Positionable.h"

namespace RedBox {
	/**
	 * Represents an axis-aligned bounding box.
	 * @ingroup Physics
	 */
	class AxisAlignedBoundingBox : public Positionable {
	public:
		/**
		 * Default constructor.
		 */
		AxisAlignedBoundingBox();

		/**
		 * Parameterized constructor.
		 * @param newPosition Starting position.
		 * @param newSize Starting size.
		 * @see RedBox::Positionable::position
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		explicit AxisAlignedBoundingBox(const Vector2 &newPosition,
		                                const Vector2 &newSize = Vector2());

		/**
		 * Copy constructor.
		 * @param src AxisAlignedBoundingBox to make a copy of.
		 */
		AxisAlignedBoundingBox(const AxisAlignedBoundingBox &src);

		/**
		 * Destructor.
		 */
		virtual ~AxisAlignedBoundingBox();

		/**
		 * Assignment operator.
		 * @param src AxisAlignedBoundingBox to make a copy of.
		 * @return Reference to the modified AxisAlignedBoundingBox.
		 */
		AxisAlignedBoundingBox &operator=(const AxisAlignedBoundingBox &src);

		/**
		 * Comparison operator. Checks if both the boxes are equivalent.
		 * @param other Other box to check equality with.
		 * @return True if the boxes have the same position and size, false if
		 * not.
		 */
		bool operator==(const AxisAlignedBoundingBox &other) const;

		/**
		 * Comparison operator. Checks if two boxes are different.
		 * @param other Other box to check non-equality with.
		 * @return True if the boxes have different position or size, false if
		 * not.
		 */
		bool operator!=(const AxisAlignedBoundingBox &other) const;

		/**
		 * Gets the bounding box's size.
		 * @return Vector2 containing the width and height of the bounding box.
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		const Vector2 getSize() const;

		/**
		 * Sets the bounding box's size.
		 * @param newSize New size to set.
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		void setSize(const Vector2 &newSize);

		/**
		 * Sets the bounding box's size.
		 * @param newWidth New width to set.
		 * @param newHeight New height to set.
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		void setSize(float newWidth, float newHeight);

		/**
		 * Gets the bounding box's width.
		 * @return Width in pixels (by default).
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		float getWidth() const;

		/**
		 * Sets the bounding box's width.
		 * @param newWidth New width to set.
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		void setWidth(float newWidth);

		/**
		 * Gets the bounding box's height.
		 * @return Height in pixels (by default).
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		float getHeight() const;

		/**
		 * Sets the bounding box's height.
		 * @param newHeight New height to set.
		 * @see RedBox::AxisAlignedBoundingBox::size
		 */
		void setHeight(float newHeight);

		/**
		 * Gets the bounding box's left side's horizontal coordinate.
		 * @return Left side's horizontal position.
		 */
		float getLeft() const;

		/**
		 * Gets the bounding box's right side's horizontal coordinate.
		 * @return Right side's horizontal coordinate.
		 */
		float getRight() const;

		/**
		 * Gets the bounding box's top side's vertical coordinate.
		 * @return Top side's vertical coordinate.
		 */
		float getTop() const;

		/**
		 * Gets the bounding box's bottom side's vertical coordinate.
		 * @return Bottom side's vertical coordinate.
		 */
		float getBottom() const;

		/**
		 * Checks if the bounding box overlaps with another bounding box.
		 * @param other Bounding box to check overlapping with.
		 * @return True if the two bounding boxes collide, false if not.
		 */
		bool overlaps(const AxisAlignedBoundingBox &other) const;

		/**
		 * Checks if a point overlaps with the bounding box.
		 * @param point Point to check overlapping with.
		 * @return True if the point is inside the bounding box, false if not.
		 */
		bool overlaps(const Vector2 &point) const;

		/**
		 * Checks if a point overlaps with the bounding box.
		 * @param xPoint Horizontal coordinate of the point to check overlapping
		 * with.
		 * @param yPoint Vertical coordinate of the point to check overlapping
		 * with.
		 * @return True if the point is inside the bounding box, false if not.
		 */
		bool overlaps(float xPoint, float yPoint) const;

		/**
		 * Checks if the bounding box overlaps with a horizontal line. If the
		 * lower boundary given is higher than the other boundary, they will
		 * be swapped.
		 * @param yPosition Vertical position of the horizontal line to check
		 * overlapping with.
		 * @param lowerXBoundary Lower horizontal boundary of the line.
		 * @param higherXBoundary Higher horizontal boundary of the line.
		 * @return True if the bounding box overlaps with the horizontal line,
		 * false if not.
		 */
		bool overlapsHorizontalLine(float yPosition,
		                            float lowerXBoundary,
		                            float higherXBoundary) const;

		/**
		 * Checks if the bounding box overlaps with a horizontal line.
		 * @param yPosition Vertical position of the horizontal line to check
		 * overlapping with.
		 * @return True if the bounding box overlaps with the horizontal line,
		 * false if not.
		 */
		bool overlapsHorizontalLine(float yPosition) const;

		/**
		 * Checks if the bounding box overlaps with a vertical line. If the
		 * lower boundary given is higher than the other boundary, they will
		 * be swapped.
		 * @param xPosition Horizontal position of the vertical line to check
		 * overlapping with.
		 * @param lowerYBoundary Lower vertical boundary of the line.
		 * @param higherYBoundary Higher vertical boundary of the line.
		 * @return True if the bounding box overlaps with the vertical line,
		 * false if not.
		 */
		bool overlapsVerticalLine(float xPosition, float lowerYBoundary,
		                          float higherYBoundary) const;

		/**
		 * Checks if the bounding box overlaps with a vertical line.
		 * @param xPosition Horizontal position of the vertical line to check
		 * overlapping with.
		 * @return True if the bounding box overlaps with the vertical line,
		 * false if not.
		 */
		bool overlapsVerticalLine(float xPosition) const;

		/**
		 * Checks whether or not the current box is completely inside another
		 * box.
		 * @param other Box to check if it completely envelops the instance.
		 * @return True if the instance is completely inside the given box,
		 * false if not.
		 */
		bool isCompletelyInside(const AxisAlignedBoundingBox &other) const;
	private:
		/// Size in pixels (by default) of the bounding box.
		Vector2 size;
	};

}

#endif
