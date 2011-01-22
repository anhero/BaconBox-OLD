/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */


#ifndef BODYLINK
#define BODYLINK

#include <vector>

#include "LinkData.h"
#include "Vertex.h"

namespace RedBox {
    class Vertex;
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
        std::vector<Vertex*>& getVertices();
    private:
        /**
         * Makes the instance a copy of the recieved Link.
         * @param src Link to make a copy of.
         */
        void copyFrom(const Link& src);
        /// Info on the Link.
        LinkData info;
        /// Vertices that the Link is made of.
        std::vector<Vertex*> vertices;
    };
}

#endif