/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_SET_H
#define RB_TILE_SET_H

#include <string>
#include <deque>

#include "Vector2.h"
#include "Texturable.h"
#include "TileMapEntity.h"
#include "TextureCoordinates.h"

namespace RedBox {
	struct TextureInformation;

	/**
	 * Represents a tileset for a tile map.
	 * @ingroup TileMap
	 */
	struct Tileset : public Texturable, public TileMapEntity {
	public:
		/// Tile size given to tilesets by default (32x32).
		static const Vector2 DEFAULT_TILE_SIZE;

		/**
		 * Default constructor.
		 */
		Tileset();

		/**
		 * Parameterized constructor.
		 * @param newTexture Texture to use for the tileset.
		 * @param newName Name of the tileset.
		 * @param newTileSize Size of the tiles (in pixels). 32x32 by default.
		 * @param newTileSpacing Spacing between the tiles in the tileset image.
		 * @param newMargin Margin around the tiles in the tileset image.
		 * @param tileOffset Offset that is applied when drawing the tiles in
		 * this tileset.
		 */
		explicit Tileset(TexturePointer newTexture,
		                 const std::string newName = std::string(),
		                 const Vector2 &newTileSize = DEFAULT_TILE_SIZE,
		                 float newTileSpacing = 0.0f,
		                 float newMargin = 0.0f,
		                 const Vector2 &newTileOffset = Vector2());

		/**
		 * Copy constructor.
		 * @param src tileset to make a copy of.
		 */
		Tileset(const Tileset &src);

		/**
		 * Destructor
		 */
		~Tileset();

		/**
		 * Assignment operator overload.
		 * @param src tileset to copy.
		 * @return Reference to the modified tileset.
		 */
		Tileset &operator=(const Tileset &src);

		/**
		 * Sets the tileset's texture information.
		 * @param newTexture New texture to use for the tileset.
		 */
		void setTextureInformation(TexturePointer newTexture);

		/**
		 * Gets the tiles' size.
		 * @return Tile size (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		const Vector2 &getTileSize() const;

		/**
		 * Sets the tiles' size.
		 * @param newTileSize New tile size (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		void setTileSize(const Vector2 &newTileSize);

		/**
		 * Sets the tiles' size.
		 * @param newTileWidth New tile width (in pixels).
		 * @param newTileHeight New tile height (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		void setTileSize(float newTileWidth, float newTileHeight);

		/**
		 * Gets the tile's width.
		 * @return Tile width (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		float getTileWidth() const;

		/**
		 * Sets the tile's width.
		 * @param newTileWidth New tile width (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		void setTileWidth(float newTileWidth);

		/**
		 * Gets the tile's height.
		 * @return Tile height (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		float getTileHeight() const;

		/**
		 * Sets the tile's height.
		 * @param newTileHeight New tile height (in pixels).
		 * @see RedBox::Tileset::tileSize
		 */
		void setTileHeight(float newTileHeight);

		/**
		 * Gets the tile spacing. The horizontal and vertical space found
		 * between tiles in the texture.
		 * @return Spacing between the tiles in the tileset's texture.
		 * @see RedBox::Tileset::tileSpacing
		 */
		float getTileSpacing() const;

		/**
		 * Gets the tile spacing. The horizontal and vertical space found
		 * between tiles in the texture.
		 * @param newTileSpacing New spacing between the tiles in the tileset's
		 * texture.
		 * @see RedBox::Tileset::tileSpacing
		 */
		void setTileSpacing(float newTileSpacing);

		/**
		 * Gets the tileset's margin.
		 * @return Margin around the tiles in the tileset's texture.
		 * @see RedBox::Tileset::margin
		 */
		float getMargin() const;

		/**
		 * Sets the tileset's margin.
		 * @param newMargin New margin around the tiles in the tileset's
		 * texture.
		 * @see RedBox::Tileset::margin
		 */
		void setMargin(float newMargin);

		/**
		 * Gets the tiles' offset.
		 * @return Offset that is applied when drawing the tiles from this
		 * tileset.
		 * @return RedBox::Tileset::tileOffset
		 */
		const Vector2 &getTileOffset() const;

		/**
		 * Sets the tiles' offset.
		 * @param newTileOffset New offset that to be applied when drawing the
		 * tiles from this tileset.
		 * @return RedBox::Tileset::tileOffset
		 */
		void setTileOffset(const Vector2 &newTileOffset);

		/**
		 * Sets the tiles' offset.
		 * @param newTileOffset New offset that to be applied when drawing the
		 * tiles from this tileset.
		 * @return RedBox::Tileset::tileOffset
		 */
		void setTileOffset(float newXTileOffset, float newYTileOffset);

		/**
		 * Gets the tiles' horizontal offset.
		 * @return Horizontal offset that is applied when drawing the tiles from
		 * this tileset.
		 * @see RedBox::Tileset::tileOffset
		 */
		float getXTileOffset() const;

		/**
		 * Sets the tiles' horizontal offset.
		 * @param newXTileOffset New horizontal offset that is applied when
		 * drawing the tiles from this tileset.
		 * @see RedBox::Tileset::tileOffset
		 */
		void setXTileOffset(float newXTileOffst);

		/**
		 * Gets the tiles' vertical offset.
		 * @return Vertical offset that is applied when drawing the tiles from
		 * this tileset.
		 * @see RedBox::Tileset::tileOffset
		 */
		float getYTileOffset() const;

		/**
		 * Sets the tiles' horizontal offset.
		 * @param newXTileOffset New horizontal offset that is applied when
		 * drawing the tiles from this tileset.
		 * @see RedBox::Tileset::tileOffset
		 */
		void setYTileOffset(float newYTileOffset);

		/**
		 * Loads the texture coordinates of a tile from a tile id.
		 * @param tileId Id of the tile to get its texture coordinates. Must be
		 * higher than the tileset's first tile id.
		 * @param textureCoordinates Array of Vector2 to write the texture
		 * coordinates to.
		 * @return True if the tile's texture coordinates were copied
		 * successfully, false if not. Loads the tileset's tiles' texture
		 * coordinates if the tileset's tiles' texture coordinates are not
		 * ready to be copied.
		 */
		bool loadTextureCoordinates(unsigned int tileId,
		                            TextureCoordinates &textureCoordinates);

		/**
		 * Loads the texture coordinates of a tile from a tile id.
		 * @param tileId Id of the tile to get its texture coordinates. Must be
		 * higher than the tileset's first tile id.
		 * @param textureCoordinates Array of Vector2 to write the texture
		 * coordinates to.
		 * @return True if the texture coordinates were loaded successfully,
		 * false if not. Does not load the texture coordinates if the tile
		 * set's tiles' texture coordinates are not ready.
		 */
		bool loadTextureCoordinates(unsigned int tileId,
		                            TextureCoordinates &textureCoordinates) const;
	private:
		/// Container used to contain the tiles' texture coordinates.
		typedef std::deque<TextureCoordinates> TileCoordinates;

		/**
		 * Calculates the texture coordinates of all the tiles so they are ready
		 * to be used to load textureCoordinates.
		 */
		void prepareTextureCoordinates();

		/**
		 * Size of the tiles. If the size is not the same as the tile map that
		 * uses the tileset, the tile graphics will overlap.
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

		/// Tile id of the first tile.
		unsigned int firstTileId;

		/// Set to true when the texture coordinates needs to be rebuilt.
		bool dirty;

		/// Vector containing the texture coordinates for each tile.
		TileCoordinates tileTextureCoordinates;
	};
}

#endif
