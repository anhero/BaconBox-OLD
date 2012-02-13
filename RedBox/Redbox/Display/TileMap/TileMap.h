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
#include "TileIdRange.h"
#include "Vector2.h"

namespace RedBox {
	class Tileset;
	class TileMapLayer;
	struct TextureInformation;

	class TileMap {
		friend class Tileset;
	public:

		TileMap();

		TileMap(const TileMap &src);

		~TileMap();

		TileMap &operator=(const TileMap &src);

		const TileCoordinate &getSizeInTiles() const;

		void setSizeInTiles(const TileCoordinate &newSizeInTiles);

		int getWidthInTiles() const;

		void setWidthInTiles(int newWidthInTiles);

		int getHeightInTiles() const;

		void setHeightInTiles(int newHeightInTiles);

		const Tileset *getTileset(unsigned int tileId) const;

		const Tileset *getTileset(const std::string &name) const;

		const Tileset *addTileset(const std::string &newName,
		                          TextureInformation *newTextureInformation,
		                          const Vector2 &newTileSize,
		                          float newTileSpacing = 0.0f,
		                          float newMargin = 0.0f,
		                          const Vector2 &newTileOffset = Vector2(),
		                          bool overwrite = false);

		void removeTileset(const std::string &tilesetName);

		/**
		 * Finds the tileset in the list of tilesets and removes it from the
		 * tilemap.
		 * @param tileset Pointer to the tileset to remove.
		 */
		void removeTileset(const Tileset *tileset);
	private:

		typedef std::list<Tileset *> TilesetContainer;
		typedef std::map<TileIdRange, const Tileset *, TileIdRange::Comparator> TilesetMapByTileId;
		typedef std::map<std::string, const Tileset *> TilesetMapByName;
		typedef std::list<TileMapLayer *> LayerContainer;

		void refreshTilesetsByTileId();

		void refreshTilesetsByName() const;

		/**
		 * Applies the tile id changes to all of the layers for the tile id's
		 * of a tileset that was deleted.
		 * @param toDestroy Range of tile id's that were destroyed and must now
		 * be reset to 0.
		 */
		void applyTilesetDestruction(const TileIdRange &toDestroy);

		void deleteLayers();
		void deleteTilesets();

		TileCoordinate sizeInTiles;

		TilesetContainer tilesets;

		TilesetMapByTileId tilesetsByTileId;

		mutable TilesetMapByName tilesetsByName;

		mutable bool dirtyTilesetsByName;

		LayerContainer layers;
	};
}

#endif
