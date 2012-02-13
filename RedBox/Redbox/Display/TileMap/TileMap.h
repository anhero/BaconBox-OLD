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

namespace RedBox {
	class Tileset;
	class TileMapLayer;

	class TileMap {
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

		Tileset *getTileset(unsigned int tileId);

		Tileset *getTileset(const std::string &name);
	private:

		typedef std::list<Tileset *> TilesetContainer;
		typedef std::map<TileIdRange, Tileset *, TileIdRange::Comparator> TilesetMapByTileId;
		typedef std::map<std::string, Tileset *> TilesetMapByName;
		typedef std::list<TileMapLayer *> LayerContainer;

		void refreshTilesetsByTileId();

		void refreshTilesetsByName();

		void applyTilesetDestruction(const TileIdRange &toDestroy);

		void deleteLayers();
		void deleteTilesets();

		TileCoordinate sizeInTiles;

		TilesetContainer tilesets;

		TilesetMapByTileId tilesetsByTileId;

		TilesetMapByName tilesetsByName;

		mutable bool dirtyByName;

		LayerContainer layers;
	};
}

#endif
