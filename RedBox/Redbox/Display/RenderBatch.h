/**
 * @file
 * @ingroup Group
 */

#ifndef RB_RENDERBATCH_H
#define RB_RENDERBATCH_H


#include <vector>
#include "Sprite.h"
#include "TextureInfo.h"

namespace RedBox{
	/** 
	 *
     * @ingroup Group
     */
	class RenderBatch{
	public:
        RenderBatch();
        virtual ~RenderBatch();

        /**
         *  Reconstruct the internal batch arrays from the sprites in the batch.
         */
        void reconstruct();

        
        /**
		 * Updates the sprites in the batch.
		 */
        void update();
        /**
		 * Renders the batch.
		 */
        void render();
        
        /**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is
		 * used to mask the next rendered sprite (if the next sprite
		 * is set as a masked sprite).
		 */
		virtual void mask();
        
		/**
		 * Undo what the mask function did. This function
		 * MUST be once after the masked sprite has been rendered.
		 */
		virtual void unmask();
        
        /**
         * Add a sprite in the batch.
         * All the sprites must use the same texture (or no texture if they
         * don't use textures.
         */
        void addSprite(Sprite * aSprite);
        
        /**
         * Remove the given sprite from the batch
         */
        void removeSprite(Sprite * aSprite);
	private:
        ///Batch of sprite
        std::set<Sprite*> sprites;
        
        ///Batch array of texture coordinate 
        Vector2 * textureCoord;
        ///Batch array of vertices
        Vector2 * vertices;
        ///Number of vertices in the batch
        unsigned int verticesCount;
       
        TextureInfo textureInfo;
	};
}

#endif
