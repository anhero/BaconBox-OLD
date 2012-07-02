/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include "BaconBox/Display/GraphicElement.h"
#include "BaconBox/Display/Collidable.h"
#include "BaconBox/Display/Layerable.h"

namespace BaconBox {
	typedef GraphicElement<Collidable, Layerable> Sprite;
}

#endif // RB_SPRITE_H
