/**
 * @file
 * @ingroup Display
 */
#ifndef RB_BATCHED_INANIMATE_SPRITE_H
#define RB_BATCHED_INANIMATE_SPRITE_H

#include "BatchedInanimateGraphicElement.h"
#include "Collidable.h"

namespace BaconBox {
	/**
	 * Represents a batched inanimate sprite. Can be initialized and manipulated
	 * while out of an inanimate sprite batch, but to be rendered, it needs to
	 * be in one.
	 */
	typedef BatchedInanimateGraphicElement<Collidable> BatchedInanimateSprite;
}

#endif // RB_BATCHED_INANIMATE_SPRITE_H
