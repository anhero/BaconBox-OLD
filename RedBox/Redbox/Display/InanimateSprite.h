/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_SPRITE_H
#define RB_INANIMATE_SPRITE_H

#include "LayeredInanimateGraphic.h"
#include "Collidable.h"

namespace RedBox {
	/// Represents an sprite that cannot be animated and can be added to a state.
	typedef LayeredInanimateGraphic<Collidable> InanimateSprite;
}

#endif
