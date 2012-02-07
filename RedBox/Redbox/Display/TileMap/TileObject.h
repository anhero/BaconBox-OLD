/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_OBJECT_H
#define RB_TILE_OBJECT_H

#include <string>

#include "TileMapObject.h"
#include "Vector2.h"

namespace RedBox {
	/**
	 * Represents a tile object in an object layer in a tile map.
	 * @ingroup TileMap
	 */
	struct TileObject : public TileMapObject {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newTileIndex Index of the tile to display the object.
		 * @param newPosition Position of the tile object in the layer (in
		 * pixels).
		 * @param newName Name of the tile object, if it has one.
		 */
		explicit TileObject(unsigned int newTileIndex = 0,
		                    const Vector2 &newPosition = Vector2(),
		                    const std::string &newName = std::string());

		/**
		 * Parameterized constructor.
		 * @param newTileIndex Index of the tile to display the object.
		 * @param newXPosition Horizontal position of the tile object on the
		 * object layer (in pixels).
		 * @param newYPosition Vertical position of the tile object on the
		 * object layer (in pixels).
		 * @param newName Name of the tile object, if it has one.
		 */
		TileObject(unsigned int newTileIndex,
		           float newXPosition,
		           float newYPosition,
		           const std::string &newName = std::string());

		/**
		 * Copy constructor.
		 * @param src TileObject to make a copy of.
		 */
		TileObject(const TileObject &src);

		/**
		 * Destructor.
		 */
		virtual ~TileObject();

		/**
		 * Assignment operator.
		 * @param src TileObject to copy.
		 * @return Reference to the modified TileObject.
		 */
		TileObject &operator=(const TileObject &src);

		/// Index of the tile to display.
		unsigned int tileIndex;
	};

}

#endif // RB_TILE_OBJECT_H
