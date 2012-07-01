/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_SET_H
#define RB_TILE_SET_H

#include <string>
#include <deque>
#include <map>

#include "Vector2.h"
#include "TileMapEntity.h"
#include "TextureCoordinates.h"
#include "PropertyMap.h"

namespace BaconBox {
	struct TextureInformation;
	class TileMap;

	/**
	 * Represents a tileset for a tile map.
	 * @ingroup TileMap
	 */
	class Tileset : public TileMapEntity {
		friend class TileMap;
	public:
		/// Container used to contain the tiles' texture coordinates.
		typedef std::deque<TextureCoordinates> TileCoordinates;
		
		typedef std::map<unsigned int, PropertyMap> TileProperties;

		/**
		 * Sets the name of the tileset. Does nothing if parent tile map already
		 * has a tileset with that name.
		 * @param newName New name to give to the tileset.
		 * @see BaconBox::TileMapEntity::name
		 */
		void setName(const std::string &newName);

		/**
		 * Gets the texture information for the tileset.
		 * @return Pointer to the texture information for the tileset.
		 */
		TextureInformation *getTextureInformation() const;

		/**
		 * Gets the tiles' size.
		 * @return Tile size (in pixels).
		 * @see BaconBox::Tileset::tileSize
		 */
		const Vector2 &getTileSize() const;

		/**
		 * Gets the tile's width.
		 * @return Tile width (in pixels).
		 * @see BaconBox::Tileset::tileSize
		 */
		float getTileWidth() const;

		/**
		 * Gets the tile's height.
		 * @return Tile height (in pixels).
		 * @see BaconBox::Tileset::tileSize
		 */
		float getTileHeight() const;

		/**
		 * Gets the tile spacing. The horizontal and vertical space found
		 * between tiles in the texture.
		 * @return Spacing between the tiles in the tileset's texture.
		 * @see BaconBox::Tileset::tileSpacing
		 */
		float getTileSpacing() const;

		/**
		 * Gets the tileset's margin.
		 * @return Margin around the tiles in the tileset's texture.
		 * @see BaconBox::Tileset::margin
		 */
		float getMargin() const;

		/**
		 * Gets the tiles' offset.
		 * @return Offset that is applied when drawing the tiles from this
		 * tileset.
		 * @return BaconBox::Tileset::tileOffset
		 */
		const Vector2 &getTileOffset() const;

		/**
		 * Gets the tiles' horizontal offset.
		 * @return Horizontal offset that is applied when drawing the tiles from
		 * this tileset.
		 * @see BaconBox::Tileset::tileOffset
		 */
		float getXTileOffset() const;

		/**
		 * Gets the tiles' vertical offset.
		 * @return Vertical offset that is applied when drawing the tiles from
		 * this tileset.
		 * @see BaconBox::Tileset::tileOffset
		 */
		float getYTileOffset() const;

		/**
		 * Loads the texture coordinates of a tile from a tile id.
		 * @param tileId Id of the tile to get its texture coordinates. Must be
		 * within range of the tileset's tiles id's.
		 * @param textureCoordinates Array of Vector2 to write the texture
		 * coordinates to.
		 * @return True if the texture coordinates were loaded successfully,
		 * false if not.
		 */
		bool loadTextureCoordinates(unsigned int tileId,
		                            TextureCoordinates &textureCoordinates) const;

		/**
		 * Gets the number of tiles the tileset contains.
		 * @return Number of tiles the tileset contains.
		 */
		TileCoordinates::size_type getNbTiles() const;

		/**
		 * Gets the tile id of the first tile contained by this tileset.
		 * @return Tile id of the first tile.
		 * @see BaconBox::Tileset::firstTileId
		 */
		unsigned int getFirstTileId() const;

		/**
		 * Checks whether or not the tile id fits in the tileset.
		 * @param tileId Tile id to check.
		 * @return Tile id received in parameter if it fits, 0 if it doesn't.
		 */
		unsigned int validateTileId(unsigned int tileId) const;

		/**
		 * Checks whether or not the tile id fits in the tileset.
		 * @param tileId Tile id to check.
		 * @return True if the tile id fits, false if not.
		 */
		bool isIdInTileset(unsigned int tileId) const;

		/**
		 * Gets the properties of a tile.
		 * @param tileId Id of the tile to find its properties.
		 * @return Pointer to the map of properties. NULL if the tile id does
		 * not fit in the tileset.
		 * @see BaconBox::Tileset::tileProperties
		 */
		PropertyMap *getTileProperties(unsigned int tileId);
		
		/**
		 * Gets the properties of a tile.
		 * @param tileId Id of the tile to find its properties.
		 * @return Pointer to the map of properties. NULL if the tile id does
		 * not fit in the tileset or if the tile doesn't have any properties.
		 * @see BaconBox::Tileset::tileProperties
		 */
		const PropertyMap *getTileProperties(unsigned int tileId) const;
		
	private:

		/**
		 * Parameterized constructor.
		 * @param newName Name of the tileset.
		 * @param newParentMap Parent tile map that owns the tileset.
		 * @param newTextureInformation Pointer to the texture information to
		 * use for the tileset.
		 * @param newTileSize Size of the tiles (in pixels). 32x32 by default.
		 * @param newTileSpacing Spacing between the tiles in the tileset image.
		 * @param newMargin Margin around the tiles in the tileset image.
		 * @param newTileOffset Offset that is applied when drawing the tiles in
		 * this tileset.
		 * @param newFirstTileId Tile id of the first tile in the tileset.
		 */
		Tileset(const std::string &newName,
		        const TileMap &newParentMap,
		        TextureInformation *newTextureInformation,
		        const Vector2 &newTileSize,
		        float newTileSpacing,
		        float newMargin,
		        const Vector2 &newTileOffset,
		        unsigned int newFirstTileId);

		/**
		 * Copy constructor.
		 * @param src Tileset to make a copy of.
		 * @param newParentMap Parent tile map to use as the owner of the new
		 * tileset.
		 */
		Tileset(const Tileset &src, const TileMap &newParentMap);

		/**
		 * Destructor
		 */
		~Tileset();

		/**
		 * Sets the tile id of the first tile contained by this tileset.
		 * @return newFirstTileId New tile id of the first tile.
		 * @see BaconBox::Tileset::firstTileId
		 */
		void setFirstTileId(unsigned int newFirstTileId);

		/**
		 * Calculates the texture coordinates of all the tiles so they are ready
		 * to be used to load textureCoordinates.
		 */
		void initializeTextureCoordinates();

		/// Pointer to the tile map that owns the tileset.
		const TileMap &parentMap;

		/// Pointer to the information on the tileset's texture.
		TextureInformation *textureInformation;

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

		/// Vector containing the texture coordinates for each tile.
		TileCoordinates tileTextureCoordinates;
		
		/// Map containing the properties of the tiles.
		TileProperties tileProperties;
	};
}

#endif
