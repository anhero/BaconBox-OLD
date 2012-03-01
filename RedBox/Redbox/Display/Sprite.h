/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include "GraphicElement.h"
#include "Collidable.h"
#include "Layerable.h"

namespace RedBox {
	typedef GraphicElement<Collidable, Layerable> Sprite;
}

#endif // RB_SPRITE_H
