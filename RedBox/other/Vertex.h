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
#include "Sprite.h"
#include "GraphicBody.h"

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
        /// Pointer to the vertex's parent sprite.
        Sprite* parentSprite;
        /// Pointer to the vertex's parent graphic body.
        GraphicBody* parentGraphicBody;
        /** 
         * Flag to know if the vertex needs to delete its links in the
         * destructor.
         */
        bool deleteLinks;
        /**
         * Makes the instance a copy of the recieved vertex.
         * @param src Vertex to make a copy of.
         */
        void copyFrom(const Vertex& src);
        /**
         * Deletes the links if necessary.
         */
        void clearLinks();
        /**
         * Deletes the links if necesseary and empties all the vectors.
         */
        void clean();
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
         * @return Vector containing pointers to all of the vertex's parent 
         * edges.
         */
        std::vector<Edge*>& getParentEdges();
        /**
         * Gets the parent links.
         * @return Vector containing pointers to all of the vertex's parent
         * links.
         */
        std::vector<Link*>& getParentLinks();
        /**
         * Gets the parent render steps.
         * @return Vector containing pointers to all of the vertex's parent
         * render steps.
         */
        std::vector<RenderStep*> getParentRenderSteps();
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
        /**
         * Gets the parent sprite.
         * @return Pointer to the parent sprite.
         */
        Sprite* getParentSprite();
        /**
         * Gets the parent graphic body.
         * @return Pointer to the parent graphic body.
         */
        GraphicBody* getParentGraphicBody();
        /**
         * Change the vertex's parent sprite.
         * @param newParentSprite New parent sprite for the vertex.
         */
        void setParentSprite(Sprite* newParentSprite);
        /**
         * Change the vertex's parent graphic body.
         * @param newParentGraphicBody New parent graphic body for the vertex.
         */
        void setParentGraphicBody(GraphicBody* newParentGraphicBody);
        /**
         * Deletes the vertex from its parent sprite.
         */
        void deleteFromParentSprite();
        /**
         * Deletes the vertex from its parent graphic body.
         */
        void deleteFromParentBody();
        /**
         * Sets the vertex to not delete its links on its destruction.
         */
        void dontDeleteLinks();
    };
}
#endif