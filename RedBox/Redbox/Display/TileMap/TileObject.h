/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_OBJECT_H
#define RB_TILE_OBJECT_H

#include <string>

#include "TileMapObject.h"
#include "Vector2.h"
#include "TileIdRange.h"

namespace RedBox {
	class TileMap;
	/**
	 * Represents a tile object in an object layer in a tile map.
	 * @ingroup TileMap
	 */
	class TileObject : public TileMapObject {
		friend class TileMap;
	public:
		/**
		 * Gets the tile's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the size.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the tile's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the tile's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		/**
		 * Gets the tile object's tile id.
		 * @return Tile id of the tile object.
		 * @see RedBox::TileObject::tileId
		 */
		unsigned int getTileId() const;

		/**
		 * Sets the tile object's tile id.
		 * @param newTileId New tile id of the tile object. Not set if the
		 * tile id does not fit in one of the tilesets' tile id range.
		 */
		void setTileId(unsigned int newTileId);
	private:
		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the tile object, if it has one.
		 * @param newPosition Position of the tile object in the layer (in
		 * pixels).
		 * @param newParentMap Reference to the map that contains this tile
		 * object.
		 * @param newTileIndex Id of the tile to display the object.
		 */
		explicit TileObject(const std::string &newName,
		                    const Vector2 &newPosition,
		                    const TileMap &newParentMap,
		                    unsigned int newTileId);

		/**
		 * Copy constructor.
		 * @param src TileObject to make a copy of.
		 */
		TileObject(const TileObject &src, const TileMap &newParentMap);

		/**
		 * Destructor.
		 */
		~TileObject();

		/**
		 * Applies the destruction of a range of tile id's. If the current tile
		 * id is within the range, the tile id is set to 0. If the current tile
		 * id is above the range, it is reduced by the range's length.
		 * @see RedBox::TileObject::tileId
		 */
		void applyTilesetDestruction(const TileIdRange &toDestroy);

		/**
		 * Const reference to the tile map that owns the object layer that
		 * contains this tile.
		 */
		const TileMap &parentMap;

		/// Id of the tile to display.
		unsigned int tileId;
	};

}

#endif // RB_TILE_OBJECT_H
