#include "TileMap.h"

#include <cassert>

#include <utility>
#include <algorithm>

#include "Tileset.h"
#include "DeleteHelper.h"
#include "TileLayer.h"

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
		if (dirtyTilesetsByName) {
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
		// The tile id 0 is for empty tiles, so we start counting the id's at 1.
		TileIdRange tmpRange(1);

		// We make the tile id's all valid.
		for (TilesetContainer::iterator i = tilesets.begin(); i != tilesets.end();
		     ++i) {
			assert(*i);
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
		for (LayerContainer::iterator i = layers.begin(); i != layers.end();
		     ++i) {
			assert(*i);
			delete *i;
		}
	}

	void TileMap::deleteTilesets() {
		for (TilesetContainer::iterator i = tilesets.begin();
		     i != tilesets.end(); ++i) {
			assert(*i);
			delete *i;
		}
	}
}
