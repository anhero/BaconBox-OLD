/**
 * @file
 * @ingroup Display
 */

#ifndef RB_VERTICES_GROUP_H
#define RB_VERTICES_GROUP_H

#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include <cstdarg>

#include "PlatformFlagger.h"

#include "Object.h"
#include "Vertex.h"

namespace RedBox {
	class Sprite;
	/**
	 * Group of Vertices for OpenGL and RedBox. Represents a group of vertices
	 * with information accessible for OpenGL and RedBox.
	 * @ingroup Display
	 */
	class VerticesGroup : public Object {
		/**
		 * Outputs the vertices group's content.
		 * @param output The ostream in which the vertices group is output.
		 * @param v Vertices group to output in the ostream.
		 * @return Resulting ostream.
		 */
		friend std::ostream& operator<<(std::ostream& output,
		                                const VerticesGroup& v);
	public:
		/**
		 * The default constructor.
		 */
		VerticesGroup();

		/**
		 * The copy constructor.
		 * @param src Vertex group to make a copy of.
		 */
		VerticesGroup(const VerticesGroup& src);

		/**
		 * The destructor.
		 */
		~VerticesGroup();

		/**
		 * The assignment operator overload.
		 * @param src Vertex group to make a copy of.
		 */
		VerticesGroup& operator=(const VerticesGroup& src);

		/**
		 * Adds a vertex to the instance. This includes resizing the vertexData
		 * array.
		 * @param x New vertex's horizontal value.
		 * @param y New vertex's vertical value.
		 */
		void addVertex(float x, float y);

		/**
		 * Adds multiple vertices. Can recieve a variable number of parameters.
		 * @param nbVertices Number of vertices to add. Each of the following
		 * parameters must be floats. The number of parameters must equal to
		 * twice the number of vertices to add. In the order, the floats are the
		 * horizontal value then the vertical value of the vertex to add,
		 * followed by the other vertices. For example, to add 4 vertices :
		 * addVertices(4, 1.3f, 3.4f, 1.0f, 0.05f, 4.33f, 2.66f, 19.0f, 84.1f)
		 */
		void addVertices(unsigned int nbVertices, ...);

		/**
		 * Gets the vertices. The vertices' values are actually pointers that
		 * point to the values in verticesData.
		 * @return Dynamic array containing the vertices.
		 */
		std::list<Vertex>& getVertices();

		/**
		 * Checks if the vertices are from the instance.
		 * @param firstVertex First vertex to check for.
		 * @param secondVertex Second vertex to check for.
		 */
		bool containsVertices(Vertex* firstVertex, Vertex* secondVertex);

		/**
		 * Gets the distance between the left-most and the right-most vertex and
		 * the distance between the lowest and the highest vertex. Using this
		 * function to get the width AND the height is faster than calling
		 * getWidth() and getHeight() separately.
		 * @return Vec2 containing the width and height.
		 */
		Vec2 getSize() const;

		/**
		 * Gets the distance between the left-most and the right-most vertex.
		 * @return Distance between the left-most and the right-most vertex.
		 */
		float getWidth() const;

		/**
		 * Gets the distance between the lowest and the highest vertex.
		 * @return Distance between the lowest and the highest vertex.
		 */
		float getHeight() const;

		/**
		 * Gets the vertices group's position. (0, 0) is at the upper left
		 * corner.
		 * @return Pair containing the horizontal position and the vertical
		 * position (in that order) of the left and top side.
		 */
		Vec2 getPosition() const;

		/**
		 * Gets the vertices group's center's position. (0, 0) is at the upper
		 * left corner.
		 * @return 2D Vector containing the center's horizontal position and the
		 * vertical position (in that order).
		 */
		Vec2 getPositionCenter() const;

		/**
		 * Sets the horizontal and vertical position.
		 * @param newXPosition New horizontal position, corresponds to the
		 * vertices group's new left position (in pixels).
		 * @param newYPosition New vertical position, corresponds to the
		 * vertices group's new top position (in pixels).
		 */
		void setPosition(float newXPosition, float newYPosition);

		/**
		 * Moves the vertices group horizontally and vertically.
		 * @param delta Adds this Vec2's horizontal and vertical value to the
		 * vertices group's horizontal and vertical position.
		 */
		void move(const Vec2& delta);

		/**
		 * Moves the vertices group horizontally and vertically.
		 * @param deltaX Adds this value to the vertices group's horizontal
		 * position.
		 * @param deltaY Adds this value to the vertices group's vertical
		 * position.
		 */
		void move(float deltaX, float deltaY);

		/**
		 * Gets the horizontal position. Higher position value means it is more
		 * to the right.
		 * @return Horizontal position (in pixels) of the left side.
		 */
		float getXPosition() const;

		/**
		 * Gets the center's horizontal position. Higher position value means it
		 * is more to the right.
		 * @return Horizontal position (in pixels) of the center.
		 */
		float getXPositionCenter() const;

		/**
		 * Sets the horizontal position.
		 * @param newXPosition New horizontal position, corresponds to the
		 * vertices group's new left position (in pixels).
		 */
		void setXPosition(float newXPosition);

		/**
		 * Move the vertices group horizontally.
		 * @param deltaX Adds this value to the vertices group's horizontal
		 * position.
		 */
		void moveX(float deltaX);

		/**
		 * Gets the vertical position. Higher position value means it is lower
		 * on the screen.
		 * @return Vertical position (in pixels) of the top side.
		 */
		float getYPosition() const;

		/**
		 * Gets the center's horizontal position. Higher position value means it
		 * is more to the bottom.
		 * @return Center's horizontal position (in pixels).
		 */
		float getYPositionCenter() const;

		/**
		 * Sets the vertical position.
		 * @param newYPosition New vertical position, corresponds to the
		 * vertices group's new top position (in pixels).
		 */
		void setYPosition(float newYPosition);

		/**
		 * Move the vertices group vertically.
		 * @param deltaY Adds this value to the vertices group's vertical
		 * position.
		 */
		void moveY(float deltaY);

		/**
		 * Scales the width and height of the vertices group using the center
		 * as the anchor point.
		 * @param factor 2D vector containing the horizontal and vertical
		 * scaling factor to apply.
		 */
		void scale(const Vec2& factor);

		/**
		 * Rotates the vertices group using the center as the anchor point.
		 * @param angle Angle used to rotate the vertices group. A positive
		 * value rotates it counter-clockwise.
		 */
		void rotate(float angle);

		/**
		 * Updates the verticesData from the instance's vertices. Will not do
		 * anything if the list of vertices has the same number of vertices as
		 * the vertices data contains.
		 * @param verticesData Data about the vertices' coordinates to update.
		 */
		void updateDataFromVertices(std::vector<float>& verticesData);
	private:
		/// List containing the vertices pointing to the vertices' data.
		std::list<Vertex> vertices;

		/**
		 * Goes through all the vertices and re-sets their pointers to floats
		 * correctly.
		 */
		void resetPointers();

		/**
		 * Makes the instance a copy of the VertexGroup recieved.
		 * @param src VerticesGroup to make a copy of.
		 */
		void copyFrom(const VerticesGroup& src);

		/**
		 * Frees all memory allocated by the vertices group.
		 */
		void clean();
	};
}

#endif
