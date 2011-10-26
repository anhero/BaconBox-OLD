/**
 * @file
 * @ingroup Display
 */
#ifndef RB_VERTICES_ARRAY_H
#define RB_VERTICES_ARRAY_H

#include <vector>

#include "Vector2.h"
#include "AxisAlignedBoundingBox.h"

namespace RedBox {
	/**
	 * Interface class for the arrays of vertices whether they are batched or
	 * not.
	 * @ingroup Display
	 */
	class VerticesArray {
	public:
		typedef std::vector<Vector2> ContainerType;
		typedef ContainerType::value_type ValueType;
		typedef ContainerType::size_type SizeType;
		typedef ContainerType::iterator Iterator;
		typedef ContainerType::const_iterator ConstIterator;
		typedef ContainerType::reverse_iterator ReverseIterator;
		typedef ContainerType::const_reverse_iterator ConstReverseIterator;
		typedef ContainerType::reference Reference;
		typedef ContainerType::const_reference ConstReference;
		typedef ContainerType::pointer Pointer;
		typedef ContainerType::const_pointer ConstPointer;

		/**
		 * Destructor.
		 */
		virtual ~VerticesArray();

		/**
		 * Comparison operator overload.
		 * @param rhs Vertices array to compare with.
		 * @return True if the two array of vertices have the same values, false
		 * if not.
		 */
		bool operator==(const VerticesArray &rhs) const;

		/**
		 * Comparison operator overload.
		 * @param rhs Vertices array to compare with.
		 * @return True if the two array of vertices have different values,
		 * false if not.
		 */
		bool operator!=(const VerticesArray &rhs) const;

		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		virtual Iterator getBegin() = 0;

		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		virtual ConstIterator getBegin() const = 0;

		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		virtual Iterator getEnd() = 0;

		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		virtual ConstIterator getEnd() const = 0;

		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		virtual ReverseIterator getReverseBegin() = 0;

		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		virtual ConstReverseIterator getReverseBegin() const = 0;

		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		virtual ReverseIterator getReverseEnd() = 0;

		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		virtual ConstReverseIterator getReverseEnd() const = 0;

		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		virtual bool isEmpty() const = 0;

		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		virtual SizeType getNbVertices() const = 0;

		/**
		 * Erases all the vertices.
		 */
		virtual void clear() = 0;

		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		virtual Iterator insert(Iterator position, ConstReference value = ValueType()) = 0;

		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		virtual void insert(Iterator position, SizeType count, ConstReference value = ValueType()) = 0;

		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		virtual Iterator erase(Iterator position) = 0;

		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		virtual Iterator erase(Iterator first, Iterator last) = 0;

		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		virtual void pushBack(ConstReference newVertex) = 0;

		/**
		 * Erases the last vertex in the array.
		 */
		virtual void popBack() = 0;

		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		virtual void resize(SizeType count, ConstReference value = ValueType()) = 0;

		/**
		 * Gets the minimum horizontal and vertical positions from the vectors.
		 * @return Vector2 containing the minimum horizontal and minimum
		 * vertical positions (array's upper left corner's position).
		 */
		const Vector2 getMinimumXY() const;

		/**
		 * Gets the minimum horizontal position.
		 * @return Minimum horizontal position (left-most horizontal position).
		 */
		float getMinimumX() const;

		/**
		 * Gets the minimum vertical position.
		 * @return Minimum vertical position (upper-most horizontal position).
		 */
		float getMinimumY() const;

		/**
		 * Gets the maximum horizontal and vertical positions from the vectors.
		 * @return Vector2 containing the maximum horizontal and maximum
		 * vertical positions (array's bottom right corner's position).
		 */
		const Vector2 getMaximumXY() const;

		/**
		 * Gets the maximum horizontal position.
		 * @return Maximum horizontal position (right-most horizontal position).
		 */
		float getMaximumX() const;

		/**
		 * Gets the maximum vertical position.
		 * @return Maximum vertical position (bottom-most horizontal position).
		 */
		float getMaximumY() const;

		/**
		 * Gets the maximum minus the minimum horizontal and vertical positions.
		 * @return Vector2 containing the width and the height of the array's
		 * vertices.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the maximum minus the minimum horizontal position.
		 * @return Array of vertices' width.
		 */
		float getWidth() const;

		/**
		 * Gets the maximum minus the minimum vertical position.
		 * @return Array of vertices' height.
		 */
		float getHeight() const;

		/**
		 * Gets the geometric center of the body. Same as the position center
		 * in symmetrical polygons, but must be overloaded for classes that
		 * support irregular polygons.
		 * @return Geometric center of the body (barycenter).
		 */
		const Vector2 getCentroid() const;

		/**
		 * Gets the sum of all its vertices. Adds all the vertices together and
		 * returns the result.
		 * @return Sum of all the array's vertices.
		 */
		const Vector2 getSumOfVertices() const;

		/**
		 * Moves the vertices horizontally and vertically.
		 * @param xDelta Value to add to the vertices' horizontal position (in
		 * pixels). Positive value moves the vertices to the right and a
		 * negative value moves the vertices to the left.
		 * @param yDelta Value to add to the vertices' vertical position (in
		 * pixels). Positive value moves the vertices down and a negative
		 * value moves the vertices up.
		 */
		void move(float xDelta, float yDelta);

		/**
		 * Scales the vertices from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 */
		void scaleFromPoint(float xScaling, float yScaling,
		                    const Vector2 &fromPoint);

		/**
		 * Rotates the vertices from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 */
		void rotateFromPoint(float rotationAngle,
		                     const Vector2 &rotationPoint);

		/**
		 * Checks if a point is inside the polygon represented by the vertices.
		 * @param point Point to check if it is inside the polygon.
		 * @return True if the point is inside the polygon, false if not.
		 */
		bool overlaps(const Vector2 &point) const;

		/**
		 * Gets the axis aligned bounding box that surronds the vertices array.
		 * @return Axis aligned bounding box for the vertices array.
		 */
		AxisAlignedBoundingBox getAxisAlignedBoundingBox() const;

		/**
		 * Checks if two polygons are intersecting (touching each other). Uses
		 * the Separating Axis Theorem.
		 * @param other VerticesArray to use for the other polygon.
		 * @return True if the polygons are intersecting, false if not.
		 */
		bool intersects(const VerticesArray &other) const;
	};
}
#endif
