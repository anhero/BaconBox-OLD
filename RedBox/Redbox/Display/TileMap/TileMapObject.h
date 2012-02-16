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
	class ObjectLayer;
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
		 * @param newParentLayer Object layer that owns the tile map object.
		 */
		explicit TileMapObject(const std::string &newName,
							   const Vector2 &newPosition,
		                       const ObjectLayer &newParentLayer);

		/**
		 * Copy constructor.
		 * @param src Tile map object to make a copy of.
		 * @param newParentLayer Object layer that owns the tile map object.
		 */
		TileMapObject(const TileMapObject &src,
		              const ObjectLayer &newParentLayer);

		/**
		 * Destructor.
		 */
		virtual ~TileMapObject();

		/// Object layer that owns the tile map object.
		const ObjectLayer &parentLayer;
	};

}

#endif // RB_TILE_MAP_OBJECT_H
