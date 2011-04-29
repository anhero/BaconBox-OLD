/**
 * @file
 * @ingroup Display
 */

#ifndef RB_VERTEX_H
#define RB_VERTEX_H

#include <iostream>
#include <vector>

#include "PlatformFlagger.h"

#include "Vec2.h"

namespace RedBox{

	
    /**
     * Represents a vertex. Vertex used for forming up shapes and physics
     * elements.
     * @ingroup Display
     */
    class Vertex {
        /**
         * Outputs the vertex's content.
         * @param output The ostream in which the vertex is output.
         * @param v Vertex to output in the ostream.
         * @return Resulting ostream.
         */
		friend std::ostream& operator<<(std::ostream& output, const Vertex& v);
    public:
        /**
         * Default constructor. Constructs a vertex at position (0,0) linked
         * to nothing.
         */
        Vertex();
        /**
         * Parametrized constructor. Constructs a vertex at the given position.
         * Positions recieved are stored in the Vec2 used for the position.
         * @param posX Horizontal position.
         * @param posY Vertical position.
		 * body.
         */
        Vertex(float posX, float posY);
        Vertex(float* posX, float* posY);
        /**
         * Copy constructor. Constructs a copy of the recieved vertex.
         * @param src Vertex to make a copy of.
         */
        Vertex(const Vertex& src);
        /**
         * Destructor.
         */
        ~Vertex();
        /**
         * Assignation operator overload. Makes the instance a copy of the
         * recieved vertex.
         * @param src Vertex to make a copy of.
         */
        Vertex& operator=(const Vertex& src);
      
        /**
         * Gets the vertex's horizontal position.
         * @return Float representing the vertex's horizontal position.
         */
        float getXPosition() const;
        /**
         * Gets the vertex's vertical position.
         * @return Float representing the vertex's vertical position.
         */
        float getYPosition() const;
        /**
         * Gets the position.
         * @return Vec2 representing the vertex's position.
         */
        Vec2& getPosition();
        /**
         * Sets the vertex's horizontal position.
         * @param xPos Vertex's new horizontal position.
         */
        void setXPosition(float xPos);
        /**
         * Sets the vertex's vertical position.
         * @param xPos Vertex's new vertical position.
         */
        void setYPosition(float yPos);
       
    private:
        /// Current position. Stores X and Y as direct values or as pointers.
        Vec2 position;

        /**
         * Makes the instance a copy of the recieved vertex.
         * @param src Vertex to make a copy of.
         */
        void copyFrom(const Vertex& src);
        /**
         * Deletes the links if necesseary and empties all the vectors.
         */
        void clean();
    };
}

#endif
