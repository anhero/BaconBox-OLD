/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */

#ifndef __VERTICES_GROUP_H
#define __VERTICES_GROUP_H

#include <vector>
#include <iostream>

#include "Vertex.h"

namespace RedBox {
	/**
	 * Group of Vertex for OpenGL and RedBox. Represents a group of vertex
	 * with information accessible for OpenGL and RedBox.
	 * @ingroup Display
	 * @ingroup Physics
	 */
	class VerticesGroup {
	private:
		/// Dynamic array containing the vertexes pointing to the vertexes' data.
		std::vector<Vertex> vertices;
		/// Array containing the vertexes' data.
        std::vector<float> verticesData;
		/**
		 * Makes the instance a copy of the VertexGroup recieved.
		 * @param src VertexGroup to make a copy of.
		 */
		void copyFrom(const VerticesGroup& src);
        /**
         * Frees all memory allocated.
         */
        void clean();
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
         * Gets the vertices. The vertices' values are actually pointers that
         * point to the values in verticesData.
         * @return Dynamic array containing the vertices.
         */
        std::vector<Vertex>& getVertices();
        /**
         * Gets the vertices.
         * @return Dynamic array containing the vertices.
         */
        std::vector<float>& getVerticesData();
        /**
         * Left shift operator overload for output with cout.
         * @param output The ostream in which VertexGroup is output.
         * @param vg VertexGroup to output in the ostream.
         * @return Resulting ostream.
         */
        friend std::ostream& operator<<(std::ostream& output, const VerticesGroup& vg) {
            output << "VertexGroup:{verticesData:[";
            int vSize = vg.vertices.size() * 2;
            for(int i = 0; i < vSize; i++){
                output << vg.verticesData[i];
                if(i != vSize - 1) {
                    output << ", ";
                }
            }
            output << "], vertices:[";
            vSize = vg.vertices.size();
            for(int i = 0; i < vSize; i++) {
                output << vg.vertices[i].position;
                if(i != vSize - 1) {
                    output << ", ";
                }
            }
            output << "}";
            return output;
        }
	};
}

#endif