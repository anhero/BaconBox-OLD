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
		 * Default constructor.
		 * @param newName Name of the tile map. Can be empty.
		 */
		TileMap(const std::string &newName = std::string());

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

		const TileCoordinate &getSizeInTiles() const;

		void setSizeInTiles(const TileCoordinate &newSizeInTiles,
		                    const TileCoordinate &offset = TileCoordinate());

		int getWidthInTiles() const;

		void setWidthInTiles(int newWidthInTiles, int offset = 0);

		int getHeightInTiles() const;

		void setHeightInTiles(int newHeightInTiles, int offset = 0);

		const Vector2 &getTileSize() const;

		void setTileSize(const Vector2 &newTileSize);

		float getTileWidth() const;

		void setTileWidth(float newTileWidth);

		float getTileHeight() const;

		void setTileHeight(float newTileHeight);

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

		const TileMapLayer *getLayer(const std::string &layerName) const;

		TileMapLayer *getLayer(const std::string &layerName);

		TileLayer *getTileLayer(const std::string &layerName);

		const TileLayer *getTileLayer(const std::string &layerName) const;

		TileLayer *pushBackTileLayer(const std::string &newLayerName,
		                             int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                             bool newVisible = true,
		                             bool overwrite = false);

		TileLayer *pushFrontTileLayer(const std::string &newLayerName,
		                              int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                              bool newVisible = true,
		                              bool overwrite = false);

		void removeLayer(const std::string &layerName);

		void removeLayer(const TileMapLayer *layer);

		ObjectLayer *getObjectLayer(const std::string &layerName);

		const ObjectLayer *getObjectLayer(const std::string &layerName) const;

		ObjectLayer *pushBackObjectLayer(const std::string &newLayerName,
		                                 int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                                 bool newVisible = true,
		                                 bool overwrite = false);

		ObjectLayer *pushFrontObjectLayer(const std::string &newLayerName,
		                                  int32_t newOpacity = Color::MAX_COMPONENT_VALUE_32,
		                                  bool newVisible = true,
		                                  bool overwrite = false);
	private:
		typedef std::list<Tileset *> TilesetContainer;
		typedef std::map<TileIdRange, Tileset *, TileIdRange::Comparator> TilesetMapByTileId;
		typedef std::map<std::string, Tileset *> TilesetMapByName;
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

		void deleteLayers();
		void deleteTilesets();

		/**
		 * Inserts a layer in the tile map.
		 * @param position Position in the list to insert the new layer.
		 * @param newLayerName Name of the new layer.
		 * @param newOpacity Opacity of the new layer.
		 * @param newVisible Wether or not the new layer should be visible.
		 * @param overwrite Wether or not to overwrite the existing layer if
		 * there is already a layer with the same name.
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

		TileCoordinate sizeInTiles;

		Vector2 tileSize;

		TilesetContainer tilesets;

		TilesetMapByTileId tilesetsByTileId;

		mutable TilesetMapByName tilesetsByName;

		mutable bool dirtyTilesetsByName;

		LayerContainer layers;

		mutable LayerMapByName layersByName;

		mutable bool dirtyLayersByName;
	};
}

#endif
