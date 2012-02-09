/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_BATCHED_TILE_H
#define RB_BATCHED_TILE_H

#include "BatchedInanimateSprite.h"

namespace RedBox {
	struct TileSet;

	class BatchedTile : public BatchedInanimateSprite {
		/**
		 * Default constructor.
		 */
		BatchedTile();

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the full texture as the size and image.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit BatchedTile(TexturePointer newTexture,
		                     const Vector2 &startingPosition = Vector2(),
		                     const Vector2 &newSize = Vector2(),
		                     const Vector2 &newTextureOffset = Vector2());

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

		BatchedTile *clone() const;

		unsigned int getTileId() const;

		void setTileId(unsigned int tileId);

		const TileSet *getTileSet() const;
	private:
		const TileSet *tileSet;

		unsigned int tileId;
	};
}
#endif
