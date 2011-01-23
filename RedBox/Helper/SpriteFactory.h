/**
 * @file
 * @ingroup Helper
 */

#ifndef __SPRITE_FACTORY_H
#define __SPRITE_FACTORY_H

#include "Sprite.h"

namespace RedBox {
	/**
	 * Factory that constructs sprites.
	 * @ingroup Helper
	 */
	class SpriteFactory {
		/**
		 * Constructs a polygon. The polygon will be constructed using the number of
		 * sides and side length recieved in the parameters. The polygons
		 * constructed are always equilateral.
		 * @param nbSides Number of sides the polygon will have.
		 * @param sideLength Length the polygon will have (in points).
		 * @return Pointer to the sprite constructed.
		 */
		static Sprite* makePolygon(unsigned int nbSides, float sideLength);
	};
}

#endif