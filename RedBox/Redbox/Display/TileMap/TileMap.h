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

		void refreshTilesetsByTileId();

		Tileset *getTileset(unsigned int tileId);

		void refreshTilesetsByName();

		Tileset *getTileset(const std::string &name);
	private:
		typedef std::vector<Tileset> TilesetVector;
		typedef std::map<TileIdRange, Tileset *, TileIdRange::Comparator> TilesetMapByTileId;
		typedef std::map<std::string, Tileset *> TilesetMapByName;

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

		TilesetVector tilesets;

		TilesetMapByTileId tilesetsByTileId;

		TilesetMapByName tilesetsByName;
	};
}

#endif
