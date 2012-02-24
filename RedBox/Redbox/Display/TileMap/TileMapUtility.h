/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_UTILITY_H
#define RB_TILE_MAP_UTILITY_H

#include "PropertyMap.h"

namespace RedBox {
	class Collidable;

	/**
	 * Contains utility functions for the tile map system.
	 * @ingroup TileMap
	 */
	class TileMapUtility {
	public:
		/**
		 * Loads a collidable's attributes from properties. See the
		 * tiled_properties.pdf for more information about the properties read.
		 * @param properties Properties to use to load the collidable.
		 * @param collidable Reference to the collidable in which to load the
		 * attributes.
		 */
		static void loadCollidableFromProperties(const PropertyMap &properties,
		                                         Collidable &collidable);
	private:
		/**
		 * Private undefined default constructor.
		 */
		TileMapUtility();
	};
}

#endif