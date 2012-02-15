/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_LAYER_H
#define RB_TILE_LAYER_H

#include <stdint.h>

#include <vector>

#include "TileMapLayer.h"
#include "TileCoordinate.h"
#include "TileIdRange.h"
#include "Color.h"

namespace RedBox {
	/**
	 * Represents a layer of tiles in a tile map. Always has the same size as
	 * the map that owns the layer. Can have a name, but it's not required.
	 * @ingroup TileMap
	 * @see RedBox::TileMap
	 */
	class TileLayer : public TileMapLayer {
		friend class TileMap;
	public:
		/**
		 * Gets the size of the layer in tiles.
		 * @return Size of the layer in tiles. Always the same as the tile map
		 * that owns the layer.
		 */
		const TileCoordinate &getSizeInTiles() const;

		/**
		 * Gets the width of the layer in tiles.
		 * @return Width of the layer in tiles. Always the same as the tile map
		 * that owns the layer.
		 */
		int getWidthInTiles() const;

		/**
		 * Gets the height of the layer in tiles.
		 * @return Height of the layer in tiles. Always the same as the tile map
		 * that owns the layer.
		 */
		int getHeightInTiles() const;

		/**
		 * Gets the instance as a tile layer, if it is one.
		 * @return Pointer to the instance as a tile layer, NULL if it's not a
		 * tile layer.
		 */
		TileLayer *asTileLayer();

		/**
		 * Gets the instance as a tile layer, if it is one.
		 * @return Pointer to the instance as a tile layer, NULL if it's not a
		 * tile layer.
		 */
		const TileLayer *asTileLayer() const;

		/**
		 * Gets the tile id of a position in the tile map.
		 * @param tileCoordinate Coordinates of the tile to check.
		 * @return Tile id of the tile at the given coordinate. 0 if the tile
		 * coordinates is out of bounds.
		 */
		unsigned int getTileId(const TileCoordinate &tileCoordinate) const;

		/**
		 * Gets the tile id of a position in the tile map.
		 * @param xTileCoordinate Horizontal coordinate of the tile to check.
		 * @param yTileCoordinate Horizontal coordinate of the tile to check.
		 * @return Tile id of the tile at the given coordinate. 0 if the tile
		 * coordinates is out of bounds.
		 */
		unsigned int getTileId(int xTileCoordinate, int yTileCoordinate) const;

		/**
		 * Sets the id of a tile in the tile layer. Does nothing if the tile
		 * coordinates are out of bounds or if the new tile id is invalid.
		 * @param tileCoordinate Coordinates of the tile to set its id.
		 * @param newTileId New tile id to set. Must fit within the tile map's
		 * tilesets' id ranges, else it will not be changed.
		 */
		void setTileId(const TileCoordinate &tileCoordinate,
		               unsigned int newTileId);

		/**
		 * Sets the id of a tile in the tile layer. Does nothing if the tile
		 * coordinates are out of bounds or if the new tile id is invalid.
		 * @param xTileCoordinate Horizontal coordinate of the tile to set its
		 * id.
		 * @param yTileCoordinate Vertical coordinate of the tile to set its id.
		 * @param newTileId New tile id to set. Must fit within the tile map's
		 * tilesets' id ranges, else it will not be changed.
		 */
		void setTileId(int xTileCoordinate, int yTileCoordinate,
		               unsigned int newTileId);

		/**
		 * Gets the opacity of the tile layer.
		 * @return Opacity of the tile layer, can be from 0 to 255.
		 */
		uint8_t getOpacity() const;

		/**
		 * Sets the opacity of the tile layer.
		 * @param newOpacity New opacity of the tile layer, can be from 0 to
		 * 255. If the given value is out of those bounds, it is set to the
		 * closer bound (to 0 if it's a negative value, to 255 if it's higher
		 * than 255).
		 */
		void setOpacity(int32_t newOpacity);

		/**
		 * Checks wether or not the tile layer is visible.
		 * @return True if the tile layer is visible, false if not.
		 * @see RedBox::TileLayer::visible
		 */
		bool isVisible() const;

		/**
		 * Sets wether or not the tile layer is visible.
		 * @param newVisible New boolean value to set if the tile layer is
		 * visible or not.
		 * @see RedBox::TileLayer::visible
		 */
		void setVisible(bool newVisible);
	private:
		/// Type of container used to store the tile data.
		typedef std::vector<unsigned int> DataContainer;
		/**
		 * Constructor.
		 * @param newParentMap Reference to the parent map that owns the tile
		 * layer.
		 * @param newName Name of the tile layer. Can be empty.
		 * @param newOpacity Opacity of the layer.
		 * @param newVisible Wether or not the layer is visible.
		 */
		explicit TileLayer(const TileMap &newParentMap,
		                   const std::string &newName = std::string(),
		                   int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                   bool newVisible = true);

		/**
		 * Copy constructor.
		 * @param src Tile layer to make a copy of.
		 * @param newParentMap Parent map of the tile layer.
		 */
		TileLayer(const TileLayer &src, const TileMap &newParentMap);

		/**
		 * Destructor.
		 */
		~TileLayer();

		/**
		 * Resizes the tile layer. Can only be called by the tile map that owns
		 * the tile layer.
		 * @param newSizeInTiles New size of the tile map.
		 * @param offset Offset to apply to the tile map if the new size is
		 * bigger. If the new size is smaller, the concerned offset is ignored.
		 * If an offset is negative, it is considered as 0. If an offset is too
		 * high, it is clamped to the maximum offset it could have.
		 */
		void setSizeInTiles(const TileCoordinate &newSizeInTiles,
		                    const TileCoordinate &offset);

		/**
		 * Sets the width of the tile layer. Can only be called by the tile map
		 * that owns the tile layer.
		 * @param newWidth New width of the tile map.
		 * @param offset Horizontal offset to apply to the tile map if the new
		 * size is bigger. If the new size is smaller, the concerned offset is
		 * ignored. If an offset is negative, it is considered as 0. If an
		 * offset is too high, it is clamped to the maximum offset it could
		 * have.
		 */
		void setWidthInTiles(int newWidth, int offset);

		/**
		 * Sets the height of the tile layer. Can only be called by the tile map
		 * that owns the tile layer.
		 * @param newHeight New height of the tile map.
		 * @param offset Vertical offset to apply to the tile map if the new
		 * size is bigger. If the new size is smaller, the concerned offset is
		 * ignored. If an offset is negative, it is considered as 0. If an
		 * offset is too high, it is clamped to the maximum offset it could
		 * have.
		 */
		void setHeightInTiles(int newHeight, int offset);

		/**
		 * Applies the destructiof id's of a tileset.
		 * @param toDestroy Range of tile id's to destroy. All tile id's in this
		 * range are reset to 0. All tile id's above the range are reduced by
		 * the range's length.
		 */
		void applyTilesetDestruction(const TileIdRange &toDestroy);

		/**
		 * Gets a duplicate of the tile layer.
		 * @param newParentMap Reference to the map that contains the clone.
		 * @return Pointer to a duplicate of the tile layer. The caller is
		 * responsible for deleting this instance.
		 */
		TileLayer *clone(const TileMap &newParentMap) const;

		/// Contains the tile id's of each tile in the tile layer.
		DataContainer data;

		/// Opacity of the tile layer.
		uint8_t opacity;

		/// Used to determine wether or not the tile layer is visible.
		bool visible;
	};
}

#endif // RB_TILE_LAYER_H
