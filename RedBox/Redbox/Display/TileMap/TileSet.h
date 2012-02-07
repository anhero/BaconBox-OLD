/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_SET_H
#define RB_TILE_SET_H

#include <string>

#include "Vector2.h"
#include "TexturePointer.h"
#include "Texturable.h"

namespace RedBox {
	/**
	 * Represents a tile set for a tile map.
	 * @ingroup TileMap
	 */
	class TileSet : public Texturable {
	public:
		/// Name given to tile sets by default ("TileSet").
		static const std::string DEFAULT_NAME;

		/// Tile size given to tile sets by default (32x32).
		static const Vector2 DEFAULT_TILE_SIZE;

		/**
		 * Default constructor.
		 */
		TileSet();

		/**
		 * Parameterized constructor.
		 * @param newTexture Texture to use for the tile set.
		 * @param newName Name to give to the tile set. Set to "TileSet" by
		 * default.
		 * @param newTileSize Size of the tiles (in pixels). 32x32 by default.
		 */
		explicit TileSet(TexturePointer &newTexture,
		                 const std::string &newName = DEFAULT_NAME,
		                 const Vector2 &newTileSize = DEFAULT_TILE_SIZE);

		/**
		 * Default and parameterized constructor.
		 * @param newTexture Texture to use for the tile set.
		 * @param newName Name to give to the tile set.
		 * @param newTileWidth Width of the tiles.
		 * @param newTileHeight Height of the tiles.
		 */
		TileSet(TexturePointer &newTexture,
		        const std::string &newName,
		        float newTileWidth,
		        float newTileHeight);

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

		/**
		 * Gets the name of the tile set.
		 * @return Name of the tile set.
		 * @see RedBox::TileSet::name
		 */
		const std::string getName() const;

		/**
		 * Sets the name of the tile set.
		 * @param newName new name of the tile set.
		 * @see RedBox::TileSet::name
		 */
		void setName(const std::string &newName);

		/**
		 * Gets the size of the tiles (in pixels).
		 * @return Size of the tiles.
		 * @see RedBox::TileSet::tileSize
		 */
		const Vector2 &getTileSize() const;

		/**
		 * Sets the tiles' size.
		 * @param newTileSize New tiles' size.
		 * @see RedBox::TileSet::tileSize
		 */
		void setTileSize(const Vector2 &newTileSize);

		/**
		 * Sets the tiles' width and height.
		 * @param newTileWidth New tiles' width.
		 * @param newTileHeight New tiles' height.
		 * @see RedBox::TileSet::tileSize
		 */
		void setTileSize(float newTileWidth, float newTileHeight);

		/**
		 * Gets the tiles' width.
		 * @return Tiles' width (in pixels).
		 * @see RedBox::TileSet::tileSize
		 */
		float getTileWidth() const;

		/**
		 * Sets the tiles' width.
		 * @param newTileWidth New tile's width.
		 * @see RedBox::TileSet::tileSize
		 */
		void setTileWidth(float newTileWidth);

		/**
		 * Gets the tiles' height.
		 * @return Tiles' height (in pixels).
		 * @see RedBox::TileSet::tileSize
		 */
		float getTileHeight() const;

		/**
		 * Sets the tiles' height.
		 * @param newTileHeight New tile's width.
		 * @see RedBox::TileSet::tileSize
		 */
		void setTileHeight(float newTileHeight);
	private:
		/// Name given to the tile set.
		std::string name;

		/**
		 * Size of the tiles. If the size is not the same as the tile map that
		 * uses the tile set, the tile graphics will overlap.
		 */
		Vector2 tileSize;
	};
}

#endif
