/**
 * @file
 * @ingroup Display
 */


#ifndef REDBOX_SPRITE
#define REDBOX_SPRITE


#include "Renderable.h"

namespace RedBox{
    /** 
     * Represents a sprite.
     * @ingroup Display
     */
	class Sprite : public Renderable {
    private:
        /**
         * Resets the sprite. Also frees up all allocated memory.
         */
        void clean();
        /**
         * Makes the instance a copy of the recieved one.
         * @param src Sprite to make a copy of.
         */
        void copyFrom(const Sprite& src);
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
        void warnVertexBodyOfDeletion();
    };
}

#endif