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

	bool TileMap::TileIdRange::Comparator::operator()(const TileMap::TileIdRange &first,
	                                                  const TileMap::TileIdRange &second) {
		return first.begin < second.begin && first.end <= second.end;
	}

	TileMap::TileIdRange::TileIdRange() : begin(0u), end(0u) {
	}

	TileMap::TileIdRange::TileIdRange(unsigned int tileId) : begin(tileId),
		end(tileId) {
	}

	TileMap::TileIdRange::TileIdRange(unsigned int newBegin,
	                                  unsigned int newEnd) : begin(newBegin),
		end(newEnd) {
	}

	TileMap::TileIdRange::TileIdRange(const TileIdRange &src) :
		begin(src.begin), end(src.end) {
	}

	TileMap::TileIdRange &TileMap::TileIdRange::operator=(const TileIdRange &src) {
		if (this != &src) {
			begin = src.begin;
			end = src.end;
		}

		return *this;
	}

	bool TileMap::TileIdRange::isWithin(unsigned int value) const {
		return value >= begin && value < end;
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
			(*i)->setFirstTileId(tmpRange.begin);
			tmpRange.end += (*i)->getNbTiles();
			tilesetsByTileId.insert(std::make_pair(tmpRange, *i));
			tmpRange.begin = tmpRange.end;
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
