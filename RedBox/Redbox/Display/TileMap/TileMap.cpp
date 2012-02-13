#include "TileMap.h"

#include <cassert>

#include <utility>
#include <algorithm>

#include "Tileset.h"
#include "DeleteHelper.h"

namespace RedBox {

	TileMap::~TileMap() {
		deleteLayers();
		deleteTilesets();
	}

	Tileset *TileMap::getTileset(unsigned int tileId) {
		TilesetMapByTileId::iterator found = tilesetsByTileId.find(tileId);

		if (found != tilesetsByTileId.end()) {
			return found->second;

		} else {
			return NULL;
		}
	}

	Tileset *TileMap::getTileset(const std::string &name) {
		if (dirtyByName) {
			refreshTilesetsByName();
		}
		TilesetMapByName::iterator found = tilesetsByName.find(name);

		if (found != tilesetsByName.end()) {
			return found->second;

		} else {
			return NULL;
		}
	}

	void TileMap::refreshTilesetsByTileId() {
		tilesetsByTileId.clear();
		TileIdRange tmpRange;

		// We make the tile id's all valid.
		for (TilesetContainer::iterator i = tilesets.begin(); i != tilesets.end();
		     ++i) {
			assert(*i);
			// We make sure the tileset is ready.
			(*i)->prepareTextureCoordinates();
			(*i)->setFirstTileId(tmpRange.min);
			tmpRange.max += (*i)->getNbTiles();
			tilesetsByTileId.insert(std::make_pair(tmpRange, *i));
			tmpRange.min = tmpRange.max;
		}
	}

	void TileMap::refreshTilesetsByName() {
		tilesetsByName.clear();

		for (TilesetContainer::iterator i = tilesets.begin();
		     i != tilesets.end(); ++i) {
			tilesetsByName.insert(std::make_pair((*i)->getName(), *i));
		}
	}

	void TileMap::applyTilesetDestruction(const TileIdRange &toDestroy) {
	}

	void TileMap::deleteLayers() {
		std::for_each(layers.begin(), layers.end(), DeletePointerDirect());
	}

	void TileMap::deleteTilesets() {
		std::for_each(tilesets.begin(), tilesets.end(), DeletePointerDirect());
	}
}
