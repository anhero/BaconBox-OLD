/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_SPRITE_GROUP_H
#define RB_INANIMATE_SPRITE_GROUP_H

#include "BaconBox/Display/InanimateSprite.h"
#include "BaconBox/SimpleBodyManager.h"
#include "BaconBox/Display/Layerable.h"

namespace BaconBox {
	/**
	 * Represents a group of inanimate sprites that can be added to the state.
	 */
	typedef SimpleBodyManager<InanimateSprite, Layerable> InanimateSpriteGroup;
}

#endif
