/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_BATCH_H
#define RB_SPRITE_BATCH_H

#include "LayeredBatch.h"
#include "BatchedSprite.h"

namespace BaconBox {
	typedef LayeredBatch<BatchedSprite> SpriteBatch;
}

#endif // RB_SPRITE_BATCH_H
