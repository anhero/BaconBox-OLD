/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include "LayeredGraphic.h"
#include "Collidable.h"

namespace RedBox {
	typedef LayeredGraphic<Collidable> Sprite;
}

#endif // RB_SPRITE_H
