/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include "ManagedGraphic.h"
#include "Collidable.h"
#include "Layerable.h"

namespace RedBox {
	typedef ManagedGraphic<Collidable, Layerable> Sprite;
}

#endif // RB_SPRITE_H
