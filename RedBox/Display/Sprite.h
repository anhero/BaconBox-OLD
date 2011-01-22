/**
 * @file
 * @ingroup Display
 */


#ifndef REDBOX_SPRITE
#define REDBOX_SPRITE

#include <list>
#include <vector>

#include "Renderable.h"
#include "VerticesGroup.h"
#include "Edge.h"
#include "RenderStep.h"

namespace RedBox{
    /** 
     * Represents a sprite.
     * @ingroup Display
     */
	class Sprite : public Renderable {
    public:
        /**
         * Default constructor.
         */
        Sprite();
        /**
         * Copy constructor.
         * @param src Sprite to make a copy of.
         */
        Sprite(const Sprite& src);
        /**
         * Assignation operator overload.
         * @param src Sprite to make a copy of.
         */
        Sprite& operator=(const Sprite& src);
        /**
         * Destructor. Frees up all allocated memory.
         */
        virtual ~Sprite();
        /**
         * Renders the sprite.
         */
        void render();
        /**
         * Creates an edge on the sprite. Creates an edge linking two vertices.
         * The vertices given must be part of the same sprite.
         * @param firstVertex Pointer to the first vertex that the edge will 
         * link.
         * @param secondVertex Pointer to the second vertex that the edge will
         * link.
         */
        void createEdge(Vertex* firstVertex, Vertex* secondVertex);
        /**
         * Creates a vertex in the vertices group.
         * @param x Horizontal position.
         * @param y Vertical position.
         */
        void createVertex(float x, float y);
        /**
         * Warns the vertices not to delete their links on their destruction.
         */
        void warnVerticesOfDeletion();   
        /**
        * Sets the parent graphic body to the vertices.
        * @param body Pointer to the parent graphic body to set.
        */
        void setParentGraphicBody(GraphicBody* body);
        /**
         * Removes the given edge from the sprite's edges.
         * @param edge Pointer to the edge to remove.
         */
        void removeEdge(Edge* edge);
    private:
        /// Vector containing the rendering steps.
        std::vector<RenderStep> renderSteps;
        /// Vertices making up the sprite.
        VerticesGroup vertices;
        /// Edges making up the sprite.
        std::list<Edge> edges;
        /**
         * Resets the sprite. Also frees up all allocated memory.
         */
        void clean();
        /**
         * Makes the instance a copy of the recieved one.
         * @param src Sprite to make a copy of.
         */
        void copyFrom(const Sprite& src);
    };
}

#endif