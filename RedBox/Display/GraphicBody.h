/**
 * @file
 * @ingroup Display
 */


#ifndef GRAPHICBODY
#define GRAPHICBODY

#include <list>

#include "Renderable.h"
#include "Sprite.h"
#include "Link.h"


namespace RedBox{
    /** 
     * @class GraphicBody
     * @ingroup Display
     * 
     *  Represent a body composed from Sprite and Link.
     * Body are used to represent entity in the game (monster, door, etc.)
     * Depending on links options and Sprite property, body can achieve a variety of effect
     * like a blob or a revolving door, etc.
     * 
     */
	class GraphicBody : public Renderable {
    private:
        /// Links linking the sprites within the graphic body.
        list<Link*> links;
        /// Sprites making up the graphic body.
        list<Sprite*> sprites;
        /**
         * Cleans up all allocated memory. Resets the instance.
         */
        void clean();
        /**
         * Makes the instance a copy of the recieved graphic body.
         * @param src Makes the instance a copy of this graphic body.
         */
        void copyFrom(const GraphicBody& src);
    public:
        /**
         * Default constructor.
         */
        GraphicBody();
        /**
         * Copy constructor.
         * @param src Graphic body to make a copy of.
         */
        GraphicBody(const GraphicBody& src);
        /**
         * Destructor 
         * Warns all child Sprite that their parent body is about to be deleted 
         * so they can warn their children Vertices.
         */
        virtual ~GraphicBody();
        /**
         * Assignation operator overload.
         * @param src Graphic body to make a copy of.
         * @return Current instance.
         */
        GraphicBody& operator=(const GraphicBody& src);
        /**
         * Renders the graphic body.
         */
        void render();
        
        /**
         * Add a Sprite as a child
         */
        Sprite* addSprite(Sprite* sprite);
        /**
         * Remove or delete the Sprite from the child sprites  
         * @param andDelete The removed Sprite will also be deleted if set to true
         * the default value is false
         */
        void removeSprite(Sprite* sprite, bool andDelete = false);
        /**
         * Add a Link as a child
         */
        Link* addLink(Link * link);
        /**
         * Remove or delete the Link from the child links  
         * @param andDelete The removed Link will also be deleted if set to true
         * the default value is false
         */
        void removeLink(Link * link, bool andDelete = false);
    };
}

#endif