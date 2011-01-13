/**
 * @file
 * @ingroup Display
 */


#ifndef GRAPHICBODY
#define GRAPHICBODY

#include "Sprite.h"
#include "Link.h"
#include <list>


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
	class GraphicBody {
    private:
        list<Link*> links;
        list<Sprite*> sprites;
        
    public:
        /**
         * Destructor 
         * Warn all child Sprite that their parent body is about to be delete so they 
         * can warn their child Vertex
         */
        ~GraphicBody();
        
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