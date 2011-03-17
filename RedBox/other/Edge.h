/**
 * @file
 * @ingroup Physics
 */
#ifdef RB_PHYSICS_ENABLED
#ifndef RB_EDGE_H
#define RB_EDGE_H

#include <cmath>
#include <iostream>

namespace RedBox {
    class Vertex;
    /**
     * Represents an edge in a shape. Keeps two pointers to the vertices linked
     * along with the distance between the two vertices.
     * @ingroup Physics
     */
    class Edge {
        /**
         * Outputs the edge's content.
         * @param output The ostream in which Edge is output.
         * @param e Edge to output in the ostream.
         * @return Resulting ostream.
         */
        friend std::ostream& operator<<(std::ostream& output, const Edge& e);
    public:
        /**
         * Default constructor. Creates an edge that has no vertices and
         * therefore has a length of 0.
         */
        Edge();
        /**
         * Parametrized constructor. Creates an edge linking the two vertices
         * recieved. It also calculates the distance between the two.
         * @param newV1 First edge's vertex.
         * @param newV2 Second edge's vertex.
         */
        Edge(Vertex* newV1, Vertex* newV2);
        /**
         * Copy constructor. Makes the new Edge a copy of the recieved one.
         * @param src Makes the instance a copy of this Edge.
         */
        Edge(const Edge& src);
        /**
         * Destructor. Does nothing explicitly.
         */
        ~Edge();
        /**
         * Assignation operator overload. Makes the current instance a copy of
         * the recieved Edge.
         * @param src Edge to make this instance a copy of.
         * @return Reference to the instance, for chaining assignations.
         */
        Edge& operator=(const Edge& src);
        /**
         * Gets the pointer to the first vertex.
         * @return Pointer to the Edge's first vertex.
         */
        Vertex* getV1();
        /**
         * Gets the pointer to the second vertex.
         * @return Pointer to the Edge's second vertex.
         */
        Vertex* getV2();
        /**
         * Sets a new vertex for the Edge. Recalculates the distance between
         * the new first vertex and the current second vertex.
         * @param newV1 Vertex to replace the Edge's first vertex.
         */
        void setV1(Vertex* newV1);
        /**
         * Sets a new vertex for the Edge. Recalculates the distance between
         * the current first vertex and the new second vertex.
         * @param newV2 Vertex to replace the Edge's second vertex.
         */
        void setV2(Vertex* newV2);
        /**
         * Recalculates the distance between the two vertices. Stores the new
         * distance in the "distance" member. Uses the pythagorean theorem to
         * calculate the distance.
         * @return New distance calculated.
         */
        float recalculateDistance();
        /**
         * Gets the distance separating the two vertices. Doesn't calculate it,
         * simply reads the distance member's value.
         * @return Distance stored in the instance's distance member.
         */
        float getDistance() const;
    private:
        /// Distance between the two vertices.
        float distance;
        /// Pointer to the edge's first vertex.
        Vertex* v1;
        /// Pointer to the edge's second vertex.
        Vertex* v2;
        /**
         * Makes the instance a copy of the recieved Edge.
         * @param src Edge to make a copy of.
         */
        void copyFrom(const Edge& src);
    };
}

#endif
#endif
