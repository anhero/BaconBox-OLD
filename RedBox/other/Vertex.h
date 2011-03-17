/**
 * @file
 * @ingroup Physics
 * @ingroup Display
 */

#ifndef RB_VERTEX_H
#define RB_VERTEX_H

#include <iostream>
#include <vector>

#include "PlatformFlagger.h"

#include "Vec2.h"

namespace RedBox{
	class Sprite;
	class RenderStep;
#ifdef RB_PHYSICS_ENABLED
	class GraphicBody;
	class Edge;
	class Link;
#endif
    /**
     * Represents a vertex. Vertex used for forming up shapes and physics
     * elements.
     * @ingroup Physics
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
		 * @param newParentSprite Pointer to the vertex's parent sprite.
		 * @param newParentGraphicBody Pointer to the vertex's parent graphic
		 * body.
         */
#ifdef RB_PHYSICS_ENABLED		
        Vertex(float posX, float posY, Sprite* newParentSprite = NULL,
			   GraphicBody* newParentGraphicBody = NULL);
#else
        Vertex(float posX, float posY, Sprite* newParentSprite = NULL);
#endif
#ifdef RB_PHYSICS_ENABLED		
        Vertex(float* posX, float* posY, Sprite* newParentSprite = NULL,
			   GraphicBody* newParentGraphicBody = NULL);
#else
        Vertex(float* posX, float* posY, Sprite* newParentSprite = NULL);
#endif
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
         * Change the vertex's parent sprite.
         * @param newParentSprite New parent sprite for the vertex.
         */
        void setParentSprite(Sprite* newParentSprite);
        /**
         * Warns that its parent sprite is about to be deleted so the vertex
         * doesn't delete its edges. Simply clears the vector of edges.
         */
        void warnOfParentSpriteDeletion();
#ifdef RB_PHYSICS_ENABLED
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
         * Gets the parent graphic body.
         * @return Pointer to the parent graphic body.
         */
        GraphicBody* getParentGraphicBody();
        /**
         * Change the vertex's parent graphic body.
         * @param newParentGraphicBody New parent graphic body for the vertex.
         */
        void setParentGraphicBody(GraphicBody* newParentGraphicBody);
        /**
         * Adds a parent link to the vertex. Checks to make sure it doesn't have
         * the same parent twice.
         * @param link Pointer to the parent link to be added.
         * @return Pointer to the link added.
         */
        Link* addParentLink(Link* link);
        /**
         * Checks if the vertex is part of the given link.
         * @param link Pointer to the link to check for.
         * @return True if the link is a parent, false if not.
         */
        bool containsParentLink(Link* link);
#endif
    private:
        /// Current position. Stores X and Y as direct values or as pointers.
        Vec2 position;
        /// Rendering steps that render this vertex.
        std::vector<RenderStep*> parentRenderSteps;
        /// Pointer to the vertex's parent sprite.
        Sprite* parentSprite;
#ifdef RB_PHYSICS_ENABLED
        /// Pointers to the edges that are linked to the edge.
        std::vector<Edge*> parentEdges;
        /// Links that use this vertex.
        std::vector<Link*> parentLinks;
        /// Pointer to the vertex's parent graphic body.
        GraphicBody* parentGraphicBody;
        Vec2 oldPosition;
        Vec2 acceleration;
		/**
         * Deletes the links if necessary.
         */
        void clearLinks();
        /**
         * Deletes the edges.
         */
        void clearEdges();
#endif
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
