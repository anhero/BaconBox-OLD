/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_SPRITE_H
#define RB_INANIMATE_SPRITE_H

#include "InanimateGraphicElement.h"
#include "Collidable.h"
#include "Layerable.h"

namespace RedBox {
	/// Represents an sprite that cannot be animated and can be added to a state.
	typedef InanimateGraphicElement<Collidable, Layerable> InanimateSprite;
}

#endif
