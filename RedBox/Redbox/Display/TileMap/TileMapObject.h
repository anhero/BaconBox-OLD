/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_OBJECT_H
#define RB_TILE_MAP_OBJECT_H

#include <string>

#include "PropertyMap.h"
#include "Vector2.h"

namespace RedBox {
	/**
	 * Base class for objects in an object layer for a tile map.
	 * @ingroup TileMap
	 */
	class TileMapObject {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newPosition Position of the tile map object in the layer (in
		 * pixels).
		 * @param newName Name of the tile map object, if it has one.
		 */
		explicit TileMapObject(const Vector2 &newPosition = Vector2(),
		                       const std::string &newName = std::string());

		/**
		 * Parameterized constructor.
		 * @param newXPosition Horizontal position of the tile map object on the
		 * object layer (in pixels).
		 * @param newYPosition Vertical position of the tile map object on the
		 * object layer (in pixels).
		 * @param newName Name of the tile map object, if it has one.
		 */
		TileMapObject(float newXPosition,
		              float newYPosition,
		              const std::string &newName = std::string());

		/**
		 * Copy constructor.
		 * @param src TileMapObject to make a copy of.
		 */
		TileMapObject(const TileMapObject &src);

		/**
		 * Destructor.
		 */
		virtual ~TileMapObject();

		/**
		 * Assignment operator.
		 * @param src TileMapObject to copy.
		 * @return Reference to the modified TileMapObject.
		 */
		TileMapObject &operator=(const TileMapObject &src);

		/// Position of the tile object in the object layer.
		Vector2 position;

		/// Name of the tile map object.
		std::string name;

		/// Properties of the tile map object.
		PropertyMap properties;
	};

}

#endif // RB_TILE_MAP_OBJECT_H
