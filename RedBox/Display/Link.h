/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */


#ifdef RB_PHYSICS_ENABLED
#ifndef BODYLINK
#define BODYLINK

#include <list>

#include "LinkData.h"
#include "GraphicBody.h"

namespace RedBox {
    /** 
     * Links tie sprites together inside a GraphicBody
     * @ingroup Display
     * @ingroup Physics
     */
	class Link {
    public:
        /**
         * Default constructor. Creates a Link that links nothing.
         */
        Link();
        /**
         * Copy constructor. Makes the instance a copy of the recieved Link.
         * @param src Link to make a copy of.
         */
        Link(const Link& src);
        /**
         * Destructor. Has nothing that needs deallocation.
         */
        ~Link();
        /**
         * Assignation operation overload.
         */
        Link& operator=(const Link& l);
        /**
         * Gets the link's info.
         * @return Reference to a struct containing the link's info.
         */
        LinkData& getInfo();
        /**
         * Gets the link's vertices.
         * @return Reference to the vector containing the link's vertices.
         */
        std::list<Vertex*>& getVertices();
        /**
         * Adds a vertex to the link.
         * @param newVertex Pointer to the vertex to add to the link.
         * @return Pointer to the added vertex.
         */
        Vertex* addVertex(Vertex* newVertex, Sprite* parentSprite = NULL, GraphicBody* parentGraphicBody = NULL);
        /**
         * Checks if the vertex is part of the link.
         * @param vertex Pointer to the vertex to check.
         * @return True if the vertex is part of the link, false if not.
         */
        bool containsVertex(Vertex* vertex);
    private:
        /**
         * Makes the instance a copy of the recieved Link.
         * @param src Link to make a copy of.
         */
        void copyFrom(const Link& src);
        /// Info on the Link.
        LinkData info;
        /// Vertices that the Link is made of.
        std::list<Vertex*> vertices;
    };
}

#endif
#ifdef RB_PHYSICS_ENABLED
