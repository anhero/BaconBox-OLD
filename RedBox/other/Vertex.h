/**
 * @file
 * @ingroup Physics
 * @ingroup Display
 */

#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <vector>

#include "Vec2.h"
#include "Edge.h"
#include "Link.h"

namespace RedBox{
    class Edge;
    class Link;
    class RenderStep;
    /**
     * Represents a vertex. Vertex used for forming up shapes and physics
     * elements.
     * @ingroup Physics
     * @ingroup Display
     */
    class Vertex {
    private:
#ifdef REDBOX_PHYSICS_ENABLED
        Vec2 oldPosition;
        Vec2 acceleration;
#endif
        /// Current position. Stores X and Y as direct values or as pointers.
        Vec2 position;
        /// Pointers to the edges that are linked to the edge.
        std::vector<Edge*> parentEdges;
        /// Links that use this vertex.
        std::vector<Link*> parentLinks;
        /// Rendering steps that render this vertex.
        std::vector<RenderStep*> parentRenderSteps;
        // TODO: Add parent GraphicBody and parent Sprite.
        /**
         * Makes the instance a copy of the recieved vertex.
         * @param src Vertex to make a copy of.
         */
        void copyFrom(const Vertex& src);
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
         */
        Vertex(float posX, float posY);
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
         * Gets the parent edges.
         * @return Vector containing pointers to all of the vertex' parent 
         * edges.
         */
        std::vector<Edge*>& getParentEdges();
        /**
         * Gets the parent links.
         * @return Vector containing pointers to all of the vertex' parent
         * links.
         */
        std::vector<Link*>& getParentLinks();
        /**
         * Gets the parent render steps.
         * @return Vector containing pointers to all of the vertex' parent
         * render steps.
         */
        std::vector<RenderStep*> getParentRenderSteps();
        /**
         * Gets the vertex' horizontal position.
         * @return Float representing the vertex' horizontal position.
         */
        float getXPosition() const;
        /**
         * Gets the vertex' vertical position.
         * @return Float representing the vertex' vertical position.
         */
        float getYPosition() const;
        /**
         * Gets the position.
         * @return Vec2 representing the vertex' position.
         */
        Vec2& getPosition();
        /**
         * Sets the vertex' horizontal position.
         * @param xPos Vertex' new horizontal position.
         */
        void setXPosition(float xPos);
        /**
         * Sets the vertex' vertical position.
         * @param xPos Vertex' new vertical position.
         */
        void setYPosition(float yPos);
        /**
         * Deletes the vertex from its parent sprite.
         */
        void deleteFromParentSprite();
        /**
         * Deletes the vertex from its parent graphic body.
         */
        void deleteFromParentBody();
    };
}
#endif