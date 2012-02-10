#include "TileMap.h"

#include <utility>

#include "Tileset.h"

namespace RedBox {
	void TileMap::refreshTilesetsByTileId() {
		tilesetsByTileId.clear();

		for (TilesetVector::iterator i = tilesets.begin(); i != tilesets.end(); ++i) {
			tilesetsByTileId.insert(std::make_pair(TileIdRange(i->getNbTiles())));
		}
	}
}
