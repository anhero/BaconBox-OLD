/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_GROUP_H
#define RB_SPRITE_GROUP_H

#include "BaconBox/Display/Sprite.h"
#include "BaconBox/SimpleBodyManager.h"
#include "BaconBox/Display/Layerable.h"

namespace BaconBox {
	/**
	 * Represents a group of sprites that can be added to the state.
	 */
	typedef SimpleBodyManager<Sprite, Layerable> SpriteGroup;
}

#endif
