/**
 * @file
 * @ingroup Group
 */

#ifndef RB_RENDERBATCH_H
#define RB_RENDERBATCH_H


#include <vector>
#include "Sprite.h"

namespace RedBox{
	/** 
	 *
     * @ingroup Group
     */
	class RenderBatch{
	public:
        RenderBatch();
        void reconstruct();
	private:
        std::vector<Sprite*> sprites;
        Vector2 * textureCoord;
        Vector2 * vertices;
        unsigned int verticesCount;
        
	};
}

#endif
