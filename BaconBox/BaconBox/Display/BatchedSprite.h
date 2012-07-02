/**
 * @file
 * @ingroup Display
 */
#ifndef RB_BATCHED_SPRITE_H
#define RB_BATCHED_SPRITE_H

#include "BaconBox/Display/Collidable.h"
#include "BaconBox/Display/BatchedGraphicElement.h"

namespace BaconBox {
	/**
	 * Represents a batched sprite. Can be initialized and manipulated while out
	 * of a sprite batch, but to be rendered, it needs to be in one.
	 */
	typedef BatchedGraphicElement<Collidable> BatchedSprite;
}

#endif // RB_BATCHED_SPRITE_H
