/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_SPRITE_H
#define RB_INANIMATE_SPRITE_H

#include "BaconBox/Display/InanimateGraphicElement.h"
#include "BaconBox/Display/Collidable.h"
#include "BaconBox/Display/Layerable.h"

namespace BaconBox {
	/// Represents an sprite that cannot be animated and can be added to a state.
	typedef InanimateGraphicElement<Collidable, Layerable> InanimateSprite;
}

#endif
