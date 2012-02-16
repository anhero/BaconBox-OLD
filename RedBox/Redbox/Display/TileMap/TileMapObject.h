/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_OBJECT_H
#define RB_TILE_MAP_OBJECT_H

#include "Vector2.h"
#include "TileMapEntity.h"
#include "Positionable.h"

namespace RedBox {
	/**
	 * Base class for objects in an object layer for a tile map.
	 * @ingroup TileMap
	 */
	class TileMapObject : public TileMapEntity, public Positionable {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the tile map object, if it has one.
		 * @param newPosition Position of the tile map object in the layer (in
		 * pixels).
		 * @see RedBox::TileMapObject::position
		 */
		explicit TileMapObject(const std::string &newName = std::string(),
							   const Vector2 &newPosition = Vector2());

		/**
		 * Copy constructor.
		 * @param src Tile map object to make a copy of.
		 */
		TileMapObject(const TileMapObject &src);

		/**
		 * Destructor.
		 */
		virtual ~TileMapObject();

		/**
		 * Assignment operator.
		 * @param src Tile map object to copy.
		 * @return Reference to the modified tile map object.
		 */
		TileMapObject &operator=(const TileMapObject &src);
	};

}

#endif // RB_TILE_MAP_OBJECT_H
