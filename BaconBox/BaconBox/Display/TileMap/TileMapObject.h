/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_OBJECT_H
#define RB_TILE_MAP_OBJECT_H

#include <string>

#include "BaconBox/Vector2.h"
#include "BaconBox/Display/TileMap/TileMapEntity.h"
#include "BaconBox/Display/Positionable.h"

namespace BaconBox {
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
		 * @param newType Name of the custom type (optional).
		 */
		TileMapObject(const std::string &newName,
		              const Vector2 &newPosition,
		              const ObjectLayer &newParentLayer,
		              const std::string &newType = std::string());

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

		/**
		 * Gets the object's custom type name.
		 * @return Name of the custom type. Can be empty.
		 * @see BaconBox::TileMapObject::type
		 */
		const std::string &getType() const;

		/**
		 * Sets the object's custom type name.
		 * @param newType New name of the custom type.
		 * @see BaconBox::TileMapObject::type
		 */
		void setType(const std::string &newType);

		/// Object layer that owns the tile map object.
		const ObjectLayer &parentLayer;

	private:
		/// Name of the custom type (optional).
		std::string type;
	};

}

#endif // RB_TILE_MAP_OBJECT_H
