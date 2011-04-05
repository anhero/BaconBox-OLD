/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */

#ifndef RB_VERTICES_GROUP_H
#define RB_VERTICES_GROUP_H

#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include <cstdarg>

#include "PlatformFlagger.h"
#include "Vertex.h"

namespace RedBox {
#ifdef RB_PHYSICS_ENABLED
	class GraphicBody;
#endif
	class Sprite;
	/**
	 * Group of Vertex for OpenGL and RedBox. Represents a group of vertex
	 * with information accessible for OpenGL and RedBox.
	 * @ingroup Display
	 * @ingroup Physics
	 */
	class VerticesGroup {
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
        
#ifdef RB_PHYSICS_ENABLED
        /**
         * Adds a vertex to the instance. This includes resizing the vertexData
         * array.
         * @param x New vertex's horizontal value.
         * @param y New vertex's vertical value.
         * @param parentSprite Pointer to the vertex's parent sprite.
         * @param parentGraphicBody Pointer to the vertex's parent graphic body.
         */
        void addVertex(float x, float y, Sprite* sprite = NULL, 
                       GraphicBody* graphicBody = NULL);
#else
        void addVertex(float x, float y, Sprite* sprite = NULL);
#endif
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
		 * Removes a vertex. Causes the vertices group to be rebuilt.
		 * @param vertexToDelete Pointer to the vertex to delete.
		 */
		void deleteVertex(Vertex* vertexToDelete);
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
         * Warns the vertices to not delete their links and edges.
         */
        void warnVerticesOfDeletion();
		/**
		 * Sets the vertices' parent sprite. Loops through the vertices list
		 * and sets the parent for each of the vertices.
		 * @param parentSprite Pointer to the new parent sprite.
		 */
		void setParentSprite(Sprite* parentSprite);
		/**
		 * Gets the distance between the left-most and the right-most vertex and
		 * the distance between the lowest and the highest vertex. Using this
		 * function to get the width AND the height is faster than calling
		 * getWidth() and getHeight() separately.
		 * @return First element in the pair contains the width and the second
		 * the height.
		 */
		std::pair<float, float> getWidthHeight() const;
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
		 * Gets the horizontal position. Higher position value means it is more
		 * to the right.
		 * @return Horizontal position (in pixels).
		 */
		float getXPosition() const;
		/**
		 * Gets the vertical position. Higher position value means it is lower
		 * on the screen.
		 */
		float getYPosition() const;
		/**
		 * Gets the vertices group's position. (0, 0) is at the upper left
		 * corner.
		 * @return Pair containing the horizontal position and the vertical
		 * position (in that order).
		 */
		std::pair<float, float> getPosition() const;
		
		/**
		 * Sets the horizontal position.
		 * @param x New horizontal position, corresponds to the vertices group's
		 * new left position (in pixels).
		 */
		void setXPosition(float x);
		/**
		 * Sets the vertical position.
		 * @param y New vertical position, corresponds to the verices group's
		 * new top position (in pixels).
		 */
		void setYPosition(float y);
		/**
		 * Sets the horizontal and vertical position.
		 * @param x New horizontal position, corresponds to the vertices group's
		 * new left position (in pixels).
		 * @param y New vertical position, corresponds to the verices group's
		 * new top position (in pixels).
		 */
		void setPosition(float x, float y);
		/**
		 * Move the vertices group horizontally.
		 * @param deltaX Adds this value to the vertices group's horizontal
		 * position.
		 */
		void moveX(float deltaX);
		/**
		 * Move the vertices group vertically.
		 * @param deltaY Adds this value to the vertices group's vertical
		 * position.
		 */
		void moveY(float deltaX);
		/**
		 * Move the vertices group horizontally and vertically.
		 * @param deltaX Adds this value to the vertices group's horizontal
		 * position.
		 * @param deltaY Adds this value to the vertices group's vertical
		 * position.
		 */
		void move(float deltaX, float deltaY);
#ifdef RB_PHYSICS_ENABLED
		/**
		 * Sets the vertices' parent graphic body. Loops through the vertices
		 * list and sets the parent for each of the vertices.
		 * @param parentSprite Pointer to the new parent graphic body.
		 */
		void setParentGraphicBody(GraphicBody* parentGraphicBody);
		/**
		 * Updates the instance's vertices from the veritcesData.
		 * @param verticesData Data about the vertices' coordinates.
		 * @param sprite Pointer to the parent sprite to use if this function
		 * is used on an empty VerticesGroup.
		 * @param graphicBody Pointer to the parent graphic body to use if this
		 * function is used on an empty VerticesGroup.
		 */
		void updateVerticesFromData(std::vector<float>& verticesData, Sprite* sprite = NULL, GraphicBody* graphicBody = NULL);
#else
		/**
		 * Updates the instance's vertices from the veritcesData.
		 * @param verticesData Data about the vertices' coordinates.
		 * @param sprite Pointer to the parent sprite to use if this function
		 * is used on an empty VerticesGroup.
		 */
		void updateVerticesFromData(std::vector<float>& verticesData, Sprite* sprite = NULL);
#endif
		/**
		 * Updates the verticesData from the instance's vertices. Will not do
		 * anything if the list of vertices has the same number of vertices as
		 * the vertices data contains.
		 * @param verticesData Data about the vertices' coordinates to update.
		 */
		void updateDataFromVertices(std::vector<float>& verticesData);
	private:
		/// Dynamic array containing the vertexes pointing to the vertexes' data.
		std::list<Vertex> vertices;
		/**
		 * Goes through all the vertices and re-sets their pointers to floats
		 * correctly.
		 */
		void resetPointers();
		/**
		 * Makes the instance a copy of the VertexGroup recieved.
		 * @param src VertexGroup to make a copy of.
		 */
		void copyFrom(const VerticesGroup& src);
        /**
         * Frees all memory allocated.
         */
        void clean();
	};
}

#endif
