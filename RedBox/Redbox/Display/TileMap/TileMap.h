/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_H
#define RB_TILE_MAP_H

#include <map>
#include <vector>
#include <list>

#include "TileCoordinate.h"
#include "TileMapEntity.h"
#include "TileIdRange.h"
#include "Vector2.h"
#include "Color.h"
#include "TexturePointer.h"
#include "TileMapLayer.h"

namespace RedBox {
	class Tileset;
	class TileMapLayer;
	struct TextureInformation;
	class TileLayer;
	class ObjectLayer;

	/**
	 * Contains data about a tile map. Structure is compatible with Tiled.
	 * @ingroup TileMap
	 */
	class TileMap : public TileMapEntity {
		friend class Tileset;
		friend class TileMapLayer;
	public:
		/**
		 * Represents the type that contains the pointers to the tile map's
		 * layers.
		 */
		typedef std::list<TileMapLayer *> LayerContainer;

		/**
		 * Represents the type that contains the pointers to the tile map's
		 * tilesets.
		 */
		typedef std::list<Tileset *> TilesetContainer;

		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the tile map. Can be empty.
		 * @param newSizeInTiles Starting size of the tile map.
		 * @param newTileSize Starting tile size.
		 * @see RedBox::TileMap::sizeInTiles
		 * @see RedBox::TileMap::tileSize
		 */
		explicit TileMap(const std::string &newName = std::string(),
		                 const TileCoordinate &newSizeInTiles = TileCoordinate(),
		                 const Vector2 &newTileSize = Vector2());

		/**
		 * Copy constructor.
		 * @param src Tile map to make a copy of.
		 */
		TileMap(const TileMap &src);

		/**
		 * Destructor.
		 */
		~TileMap();

		/**
		 * Assignment operator overload.
		 * @param src Tile map to copy.
		 * @return Reference to the modified tile map.
		 */
		TileMap &operator=(const TileMap &src);

		/**
		 * Gets the tile map's size in tiles.
		 * @return Size of the map in tiles.
		 * @see RedBox::TileMap::sizeInTiles
		 */
		const TileCoordinate &getSizeInTiles() const;

		/**
		 * Sets the tile map's size in tiles.
		 * @param newSizeInTiles New size in tiles.
		 * @param offset Offset to apply if the new size is bigger.
		 */
		void setSizeInTiles(const TileCoordinate &newSizeInTiles,
		                    const TileCoordinate &offset = TileCoordinate());

		/**
		 * Gets the map width in tiles.
		 * @return Map width in tiles.
		 * @see RedBox::TileMap::sizeInTiles
		 */
		int getWidthInTiles() const;

		/**
		 * Sets the width of the map in tiles.
		 * @param newWidthInTiles New width in tiles.
		 * @param offset Horizontal offset to apply if the new width is bigger.
		 */
		void setWidthInTiles(int newWidthInTiles, int offset = 0);

		/**
		 * Gets the map height in tiles.
		 * @return Map height in tiles.
		 * @see RedBox::TileMap::sizeInTiles
		 */
		int getHeightInTiles() const;

		/**
		 * Sets the height of the map in tiles.
		 * @param newHeightInTiles New height in tiles.
		 * @param offset Vertical offset to apply if the new height is bigger.
		 */
		void setHeightInTiles(int newHeightInTiles, int offset = 0);

		/**
		 * Gets the size of the tiles.
		 * @return Size of the tiles.
		 * @see RedBox::TileMap::tileSize
		 */
		const Vector2 &getTileSize() const;

		/**
		 * Sets the size of the tiles.
		 * @param newTileSize New tile size.
		 * @see RedBox::TileMap::tileSize
		 */
		void setTileSize(const Vector2 &newTileSize);

		/**
		 * Sets the size of the tiles.
		 * @param newTileWidth New tile width.
		 * @param newTileHeight New tile height.
		 * @see RedBox::TileMap::tileSize
		 */
		void setTileSize(float newTileWidth, float newTileHeight);

		/**
		 * Gets the width of the tiles.
		 * @return Width of the tiles.
		 * @see RedBox::TileMap::tileSize
		 */
		float getTileWidth() const;

		/**
		 * Sets the width of the tiles.
		 * @param newTileWidth New tile width.
		 * @see RedBox::TileMap::tileSize
		 */
		void setTileWidth(float newTileWidth);

		/**
		 * Gets the height of the tiles.
		 * @return Height of the tiles.
		 * @see RedBox::TileMap::tileSize
		 */
		float getTileHeight() const;

		/**
		 * Sets the height of the tiles.
		 * @param newTileHeight New tile height.
		 * @see RedBox::TileMap::tileSize
		 */
		void setTileHeight(float newTileHeight);

		/**
		 * Gets the tilesets.
		 * @return List containing the pointers to the tilesets.
		 * @see RedBox::TileMap::tilesets
		 */
		const TilesetContainer &getTilesets() const;

		/**
		 * Finds the tileset that has a specific tile id in its range.
		 * @param tileId Id of the tile in the tileset to find.
		 * @return Pointer to the tileset found. NULL if the tile id is too
		 * high.
		 */
		const Tileset *getTileset(unsigned int tileId) const;

		/**
		 * Finds the tileset that has a specific tile id in its range.
		 * @param tileId Id of the tile in the tileset to find.
		 * @return Pointer to the tileset found. NULL if the tile id is too
		 * high.
		 */
		Tileset *getTileset(unsigned int tileId);

		/**
		 * Finds a tileset by its name.
		 * @param name Name of the tileset to find.
		 * @return Pointer to the tileset found. NULL if no tileset was found
		 * with the given name.
		 */
		const Tileset *getTileset(const std::string &name) const;

		/**
		 * Finds a tileset by its name.
		 * @param name Name of the tileset to find.
		 * @return Pointer to the tileset found. NULL if no tileset was found
		 * with the given name.
		 */
		Tileset *getTileset(const std::string &name);

		/**
		 * Adds a tileset to the tile map.
		 * @param newName Name of the tileset.
		 * @param newTextureInformation Pointer to the texture information to
		 * use for the tileset.
		 * @param newTileSize Size of the tiles (in pixels). 32x32 by default.
		 * @param newTileSpacing Spacing between the tiles in the tileset image.
		 * @param newMargin Margin around the tiles in the tileset image.
		 * @param tileOffset Offset that is applied when drawing the tiles in
		 * this tileset.
		 * @param overwrite Set this to true if you want to overwrite the
		 * existing tileset if there is already a tileset with the same name.
		 * @return Pointer to the added tileset. If a tileset already exists
		 * with the name of the new tileset, the existing tileset is returned.
		 */
		Tileset *addTileset(const std::string &newName,
		                    TexturePointer newTextureInformation,
		                    const Vector2 &newTileSize,
		                    float newTileSpacing = 0.0f,
		                    float newMargin = 0.0f,
		                    const Vector2 &newTileOffset = Vector2(),
		                    bool overwrite = false);

		/**
		 * Finds the tileset by its name and removes it, does nothing if no
		 * tileset have that name.
		 * @param tilesetName Name of the tileset to remove.
		 * @see RedBox::TileMap::removeTileset(const Tileset *tileset)
		 */
		void removeTileset(const std::string &tilesetName);

		/**
		 * Finds the tileset in the list of tilesets and removes it from the
		 * tilemap. Tile id's that referenced this tileset will be reset to 0.
		 * @param tileset Pointer to the tileset to remove.
		 */
		void removeTileset(const Tileset *tileset);

		/**
		 * Gets the layers.
		 * @return List of pointers to the layers.
		 * @see RedBox::TileMap::layers
		 */
		const LayerContainer &getLayers() const;

		/**
		 * Gets a layer.
		 * @param layerName Name of the layer to find.
		 * @return Pointer to the layer found, NULL if none was found with the
		 * specified name.
		 * @see RedBox::TileMap::layersByName
		 */
		const TileMapLayer *getLayer(const std::string &layerName) const;

		/**
		 * Gets a layer.
		 * @param layerName Name of the layer to find.
		 * @return Pointer to the layer found, NULL if none was found with the
		 * specified name.
		 * @see RedBox::TileMap::layersByName
		 */
		TileMapLayer *getLayer(const std::string &layerName);

		/**
		 * Gets a tile layer.
		 * @param layerName Name of the tile layer to find.
		 * @return Pointer to the tile layer found, NULL if none was found with
		 * the specified name.
		 */
		TileLayer *getTileLayer(const std::string &layerName);

		/**
		 * Gets a tile layer.
		 * @param layerName Name of the tile layer to find.
		 * @return Pointer to the tile layer found, NULL if none was found with
		 * the specified name.
		 */
		const TileLayer *getTileLayer(const std::string &layerName) const;

		/**
		 * Adds a tile layer to the back of the tile map.
		 * @param newLayerName Name of the new layer.
		 * @param newOpacity Opacity of the new Layer.
		 * @param newVisible Wether or not the new layer is to be visible.
		 * @param overwrite Wether or not to overwrite the existing layer if
		 * a layer already exists with the same name.
		 * @return Pointer to the created layer.
		 */
		TileLayer *pushBackTileLayer(const std::string &newLayerName,
		                             int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                             bool newVisible = true,
		                             bool overwrite = false);

		/**
		 * Adds a tile layer to the front of the tile map.
		 * @param newLayerName Name of the new layer.
		 * @param newOpacity Opacity of the new Layer.
		 * @param newVisible Wether or not the new layer is to be visible.
		 * @param overwrite Wether or not to overwrite the existing layer if
		 * a layer already exists with the same name.
		 * @return Pointer to the created layer.
		 */
		TileLayer *pushFrontTileLayer(const std::string &newLayerName,
		                              int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                              bool newVisible = true,
		                              bool overwrite = false);

		/**
		 * Gets an object layer.
		 * @param layerName Name of the object layer to find.
		 * @return Pointer to the object layer found, NULL if none was found
		 * with the specified name.
		 */
		ObjectLayer *getObjectLayer(const std::string &layerName);

		/**
		 * Gets an object layer.
		 * @param layerName Name of the object layer to find.
		 * @return Pointer to the object layer found, NULL if none was found
		 * with the specified name.
		 */
		const ObjectLayer *getObjectLayer(const std::string &layerName) const;

		/**
		 * Adds an object layer to the back of the tile map.
		 * @param newLayerName Name of the new layer.
		 * @param newOpacity Opacity of the new Layer.
		 * @param newVisible Wether or not the new layer is to be visible.
		 * @param overwrite Wether or not to overwrite the existing layer if
		 * a layer already exists with the same name.
		 * @return Pointer to the created layer.
		 */
		ObjectLayer *pushBackObjectLayer(const std::string &newLayerName,
		                                 int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                                 bool newVisible = true,
		                                 bool overwrite = false);

		/**
		 * Adds an object layer to the front of the tile map.
		 * @param newLayerName Name of the new layer.
		 * @param newOpacity Opacity of the new Layer.
		 * @param newVisible Wether or not the new layer is to be visible.
		 * @param overwrite Wether or not to overwrite the existing layer if
		 * a layer already exists with the same name.
		 * @return Pointer to the created layer.
		 */
		ObjectLayer *pushFrontObjectLayer(const std::string &newLayerName,
		                                  int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                                  bool newVisible = true,
		                                  bool overwrite = false);

		/**
		 * Removes a layer. If the specified layer is not found, nothing is
		 * removed.
		 * @param layerName Name of the layer to remove.
		 */
		void removeLayer(const std::string &layerName);

		/**
		 * Removes a layer. If the specified layer is not found, nothing is
		 * removed.
		 * @param layer Pointer to the layer to remove.
		 */
		void removeLayer(const TileMapLayer *layer);
	private:
		/// Map of tilesets by their tile id ranges.
		typedef std::map<TileIdRange, Tileset *, TileIdRange::Comparator> TilesetMapByTileId;

		/// Map of tilesets by their name.
		typedef std::map<std::string, Tileset *> TilesetMapByName;

		/// Map of layers by their name.
		typedef std::map<std::string, TileMapLayer *> LayerMapByName;

		/**
		 * Refreshes the map of tilesets by their id.
		 */
		void refreshTilesetsByTileId();

		/**
		 * Refreshes the map of tilesets by their name.
		 */
		void refreshTilesetsByName() const;

		/**
		 * Refreshes the map of layers by their name.
		 */
		void refreshLayersByName() const;

		/**
		 * Applies the tile id changes to all of the layers for the tile id's
		 * of a tileset that was deleted.
		 * @param toDestroy Range of tile id's that were destroyed and must now
		 * be reset to 0.
		 */
		void applyTilesetDestruction(const TileIdRange &toDestroy);

		/**
		 * Frees up all memory used by the layers.
		 */
		void deleteLayers();

		/**
		 * Frees up all memory used by the tilesets.
		 */
		void deleteTilesets();

		/**
		 * Inserts a layer in the tile map.
		 * @param position Position in the list to insert the new layer.
		 * @param newLayerName Name of the new layer.
		 * @param newOpacity Opacity of the new layer.
		 * @param newVisible Wether or not the new layer should be visible.
		 * @param overwrite Wether or not to overwrite the existing layer if
		 * there is already a layer with the same name.
		 * @tparam Either TileLayer or ObjectLayer. Must be explicitly
		 * specified.
		 */
		template <typename T>
		TileMapLayer *insertLayer(LayerContainer::iterator position,
		                          const std::string &newLayerName,
		                          int32_t newOpacity,
		                          bool newVisible,
		                          bool overwrite) {
			TileMapLayer *result = getLayer(newLayerName);

			if (result) {
				if (overwrite) {
					removeLayer(result);
					insertLayer<T>(position,
					               newLayerName,
					               newOpacity,
					               newVisible,
					               false);
				}

			} else {
				layers.insert(position, new T(newLayerName, *this, newOpacity, newVisible));
				--position;

				if (!newLayerName.empty()) {
					dirtyLayersByName = true;
				}

				result = *position;
			}

			return result;
		}

		/// Size of the map in tiles.
		TileCoordinate sizeInTiles;

		/**
		 * Size of a tile. Determines the general grid size of the map. The
		 * individual tiles may have different sizes. Larger tiles will expand
		 * at the top and right (anchored to the bottom left).
		 */
		Vector2 tileSize;

		/// List of tilesets.
		TilesetContainer tilesets;

		/// Tilesets sorted by their tile id ranges.
		TilesetMapByTileId tilesetsByTileId;

		/// Tilesets sorted by their name.
		mutable TilesetMapByName tilesetsByName;

		/**
		 * Boolean used internally to determine if the map of tilesets by their
		 * name is synchronized correctly.
		 */
		mutable bool dirtyTilesetsByName;

		/// List of layers (object and tile layers).
		LayerContainer layers;

		/// Layers sorted by their name.
		mutable LayerMapByName layersByName;

		/**
		 * Boolean used internally to determine if the map of layers by their
		 * name is synchronized correctly.
		 */
		mutable bool dirtyLayersByName;
	};
}

#endif
