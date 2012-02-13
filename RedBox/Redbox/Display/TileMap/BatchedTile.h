#if 0
/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_BATCHED_TILE_H
#define RB_BATCHED_TILE_H

#include "BatchedInanimateSprite.h"

namespace RedBox {
	class Tileset;

	class BatchedTile : public BatchedInanimateSprite {
	public:
		/**
		 * Default constructor.
		 */
		BatchedTile();

		/**
		 * Parameterized constructor.
		 */
		BatchedTile(Tileset *newTileset,
		            unsigned int newTileId,
		            const Vector2 &startingPosition = Vector2());

		/**
		 * Copy constructor.
		 * @param src Batched inanimate sprite to make a copy of.
		 */
		BatchedTile(const BatchedTile &src);

		/**
		 * Destructor.
		 */
		~BatchedTile();

		/**
		 * Assignation operator overload.
		 * @param src Batched inanimate sprite to make a copy of.
		 * @return Batched inanimate sprite resulting of the copy.
		 */
		BatchedTile &operator=(const BatchedTile &src);

		/**
		 * Clones the instance of the batched tile.
		 * @return Duplicate of this batched tile. The caller is responsible
		 * for the ownership of this newly created batched tile.
		 */
		BatchedTile *clone() const;

		/**
		 * Gets the batched tile's id.
		 * @return Tile's id.
		 * @see RedBox::BatchedTile::tileId;
		 */
		unsigned int getTileId() const;

		/**
		 * Sets the batched tile's id. Changes the tile's graphic and loads
		 * the correct texture coordinates. If the tile id given is not in the
		 * tile's tileset, nothing happens.
		 * @param newTileId New tile id.
		 */
		void setTileId(unsigned int newTileId);

		/**
		 * Gets the tileset the tile is from.
		 * @return Pointer to the batched tile's tileset.
		 * @see RedBox::BatchedTile::tileset
		 */
		Tileset *getTileset() const;

		/**
		 * Reconstructs the tile's vertices and texture coordinates using the
		 * current tileset and tile id. If the tile id doesn't fit in the
		 * tileset, this function will not do anything.
		 */
		void reconstruct();

		/**
		 * Sets the tile's tileset and tile id and reconstructs the tile's
		 * vertices and tile id. If the new tile id does not fit in the tileset,
		 * nothing will happen.
		 * @param newTileset Pointer to the batched tile's new tileset.
		 * @param newTileId New tile id. If it doesn't fit in the tileset,
		 * the tile will not have any graphics.
		 * @see RedBox::BatchedTile::reconstruct()
		 */
		void construct(Tileset *newTileset, unsigned int newTileId);
	private:
		/// Pointer to the tileset the tile is part of.
		Tileset *tileset;

		/// Id of the tile in the tileset.
		unsigned int tileId;
	};
}
#endif

#endif
