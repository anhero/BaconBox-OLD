/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_H
#define RB_TILE_MAP_H

#include <map>
#include <vector>

namespace RedBox {
	class Tileset;

	class TileMap {
	public:

		TileMap();

		TileMap(const TileMap &src);

		TileMap &operator=(const TileMap &src);

		void refreshTilesetsByTileId();

		Tileset *getTileset(unsigned int tileId);

		void refreshTilesetsByName();

		Tileset *getTileset(const std::string &name);
	private:

		struct TileIdRange {
			struct Comparator {
				bool operator()(const TileIdRange &first, const TileIdRange &second);
			};

			TileIdRange();
			TileIdRange(unsigned int tileId);
			TileIdRange(unsigned int newBegin, unsigned int newEnd);
			TileIdRange(const TileIdRange &src);

			TileIdRange &operator=(const TileIdRange &src);

			unsigned int begin;
			unsigned int end;
		};

		typedef std::vector<Tileset> TilesetVector;
		typedef std::map<TileIdRange, Tileset *, TileIdRange::Comparator> TilesetMapByTileId;
		typedef std::map<std::string, Tileset *> TilesetMapByName;

		TilesetVector tilesets;

		TilesetMapByTileId tilesetsByTileId;

		TilesetMapByName tilesetsByName;
	};
}

#endif
