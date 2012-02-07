/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_SET_H
#define RB_TILE_SET_H

#include "Vector2.h"
#include "TexturePointer.h"
#include "PropertyMap.h"
#include "Color.h"

namespace RedBox {
	struct TextureInformation;

	/**
	 * Represents a tile set for a tile map.
	 * @ingroup TileMap
	 */
	struct TileSet {
	public:
		/// Tile size given to tile sets by default (32x32).
		static const Vector2 DEFAULT_TILE_SIZE;

		/**
		 * Default constructor.
		 */
		TileSet();

		/**
		 * Parameterized constructor.
		 * @param newTexture Texture to use for the tile set.
		 * @param newTileSize Size of the tiles (in pixels). 32x32 by default.
		 * @param newTileSpacing Spacing between the tiles in the tileset image.
		 * @param newMargin Margin around the tiles in the tileset image.
		 * @param tileOffset Offset that is applied when drawing the tiles in
		 * this tileset.
		 */
		explicit TileSet(TexturePointer newTexture,
		                 const Vector2 &newTileSize = DEFAULT_TILE_SIZE,
		                 float newTileSpacing = 0.0f,
		                 float newMargin = 0.0f,
		                 const Vector2 &newTileOffset = Vector2());

		/**
		 * Default and parameterized constructor.
		 * @param newTexture Texture to use for the tile set.
		 * @param newTileWidth Width of the tiles.
		 * @param newTileHeight Height of the tiles.
		 * @param newTileSpacing Spacing between the tiles in the tileset image.
		 * @param newMargin Margin around the tiles in the tileset image.
		 * @param tileOffset Offset that is applied when drawing the tiles in
		 * this tileset.
		 */
		TileSet(TexturePointer newTexture,
		        float newTileWidth,
		        float newTileHeight,
		        float newTileSpacing = 0.0f,
                float newMargin = 0.0f,
                const Vector2 &newTileOffset = Vector2());

		/**
		 * Copy constructor.
		 * @param src Tile set to make a copy of.
		 */
		TileSet(const TileSet &src);

		/**
		 * Assignment operator overload.
		 * @param src Tile set to copy.
		 * @return Reference to the modified tile set.
		 */
		TileSet &operator=(const TileSet &src);

		/// Texture to use as the tile set.
		TextureInformation *textureInformation;

		/**
		 * Size of the tiles. If the size is not the same as the tile map that
		 * uses the tile set, the tile graphics will overlap.
		 */
		Vector2 tileSize;

		/**
		 * Spacing between the tiles in the tileset image.
		 */
		float tileSpacing;

		/**
		 * Margin around the tiles in the tileset image.
		 */
		float margin;

		/**
		 * Offset that is applied when drawing the tiles in this tileset.
		 */
		Vector2 tileOffset;

		/**
		 * Color that is applied on each tile when rendering them (white by
		 * default).
		 */
		Color tileColor;

		/**
		 * Map of properties.
		 */
		PropertyMap properties;
	};
}

#endif
