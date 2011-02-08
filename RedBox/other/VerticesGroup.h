/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */

#ifndef __VERTICES_GROUP_H
#define __VERTICES_GROUP_H

#include <vector>
#include <list>
#include <iostream>
#include <pair>

#include "Vertex.h"

namespace RedBox {
	/**
	 * Group of Vertex for OpenGL and RedBox. Represents a group of vertex
	 * with information accessible for OpenGL and RedBox.
	 * @ingroup Display
	 * @ingroup Physics
	 */
	class VerticesGroup {
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
         * @param parentSprite Pointer to the vertex's parent sprite.
         * @param parentGraphicBody Pointer to the vertex's parent graphic body.
         */
#ifdef RB_PHYSICS_ENABLED
        void addVertex(float x, float y, Sprite* sprite = NULL, 
                       GraphicBody* graphicBody = NULL);
#else
        void addVertex(float x, float y, Sprite* sprite = NULL);
#endif
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
         * Gets the vertices.
         * @return Dynamic array containing the vertices.
         */
        std::vector<float>& getVerticesData();
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
#ifdef RB_PHYSICS_ENABLED
		/**
		 * Sets the vertices' parent graphic body. Loops through the vertices
		 * list and sets the parent for each of the vertices.
		 * @param parentSprite Pointer to the new parent graphic body.
		 */
		void setParentGraphicBody(GraphicBody* parentGraphicBody);
#endif
	private:
		/// Dynamic array containing the vertexes pointing to the vertexes' data.
		std::list<Vertex> vertices;
		/// Array containing the vertexes' data.
        std::vector<float> verticesData;
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

#include "RenderStep.h"

#endif