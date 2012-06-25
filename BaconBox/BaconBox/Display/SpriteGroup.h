/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_GROUP_H
#define RB_SPRITE_GROUP_H

#include "Sprite.h"
#include "SimpleBodyManager.h"
#include "Layerable.h"

namespace BaconBox {
	/**
	 * Represents a group of sprites that can be added to the state.
	 */
	typedef SimpleBodyManager<Sprite, Layerable> SpriteGroup;
}

#endif