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

	const TileCoordinate &TileMap::getSizeInTiles() const {
		return sizeInTiles;
	}

	void TileMap::setSizeInTiles(const TileCoordinate &newSizeInTiles,
	                             const TileCoordinate &offset) {
		if (newSizeInTiles.getX() >= 0 && newSizeInTiles.getY() >= 0) {
			for (LayerContainer::iterator i = layers.begin(); i != layers.end();
			     ++i) {
				if ((*i)->asTileLayer()) {
					(*i)->asTileLayer()->setSizeInTiles(newSizeInTiles, offset);
				}
			}

			sizeInTiles = newSizeInTiles;
		}
	}

	int TileMap::getWidthInTiles() const {
		return sizeInTiles.getX();
	}

	void TileMap::setWidthInTiles(int newWidthInTiles, int offset) {
		if (newWidthInTiles >= 0) {
			for (LayerContainer::iterator i = layers.begin(); i != layers.end();
			     ++i) {
				if ((*i)->asTileLayer()) {
					(*i)->asTileLayer()->setWidthInTiles(newWidthInTiles, offset);
				}
			}

			sizeInTiles.setX(newWidthInTiles);
		}
	}

	int TileMap::getHeightInTiles() const {
		return sizeInTiles.getY();
	}

	void TileMap::setHeightInTile(int newHeightInTiles, int offset) {
		if (newHeightInTiles >= 0) {
			for (LayerContainer::iterator i = layers.begin(); i != layers.end();
			     ++i) {
				if ((*i)->asTileLayer()) {
					(*i)->asTileLayer()->setHeightInTiles(newHeightInTiles, offset);
				}
			}

			sizeInTiles.setY(newHeightInTiles);
		}
	}

	const Vector2 &TileMap::getTileSize() const {
		return tileSize;
	}

	void TileMap::setTileSize(const Vector2 &newTileSize) {
		tileSize = newTileSize;
	}

	float TileMap::getTileWidth() const {
		return tileSize.getX();
	}

	void TileMap::setTileWidth(float newTileWidth) {
		tileSize.setX(newTileWidth);
	}

	float TileMap::getTileHeight() const {
		return tileSize.getY();
	}

	void TileMap::setTileHeight(float newTileHeight) {
		tileSize.setY(newTileHeight);
	}

	const Tileset *TileMap::getTileset(unsigned int tileId) const {
		TilesetMapByTileId::const_iterator found = tilesetsByTileId.find(tileId);

		if (found != tilesetsByTileId.end()) {
			return found->second;

		} else {
			return NULL;
		}
	}

	const Tileset *TileMap::getTileset(const std::string &name) const {
		if (dirtyTilesetsByName) {
			refreshTilesetsByName();
		}

		TilesetMapByName::const_iterator found = tilesetsByName.find(name);

		if (found != tilesetsByName.end()) {
			return found->second;

		} else {
			return NULL;
		}
	}

	const Tileset *TileMap::addTileset(const std::string &newName,
	                                   TextureInformation *newTextureInformation,
	                                   const Vector2 &newTileSize,
	                                   float newTileSpacing,
	                                   float newMargin,
	                                   const Vector2 &newTileOffset,
	                                   bool overwrite) {
		const Tileset *result = getTileset(newName);

		if (result) {
			if (overwrite) {
				removeTileset(result);
				addTileset(newName,
				           newTextureInformation,
				           newTileSize,
				           newTileSpacing,
				           newMargin,
				           newTileOffset,
				           false);

			} else {
				result = NULL;
			}

		} else {
			unsigned int firstTileId = (tilesets.empty()) ? (1) : (tilesets.back()->getFirstTileId() + tilesets.back()->getNbTiles());
			tilesets.push_back(new Tileset(newName, this, newTextureInformation, newTileSize, newTileSpacing, newMargin, newTileOffset, firstTileId));
			tilesetsByTileId.insert(std::make_pair(TileIdRange(tilesets.back()->getFirstTileId(), tilesets.back()->getFirstTileId() + tilesets.back()->getNbTiles()),
			                                       tilesets.back()));
		}

		return result;
	}

	void TileMap::removeTileset(const std::string &tilesetName) {
		removeTileset(getTileset(tilesetName));
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

	void TileMap::refreshTilesetsByName() const {
		tilesetsByName.clear();

		for (TilesetContainer::const_iterator i = tilesets.begin();
		     i != tilesets.end(); ++i) {
			tilesetsByName.insert(std::make_pair((*i)->getName(), *i));
		}
	}

	void TileMap::removeTileset(const Tileset *tileset) {
		if (tileset) {
			TilesetContainer::iterator found = std::find(tilesets.begin(), tilesets.end(), tileset);

			if (found != tilesets.end()) {
				applyTilesetDestruction(TileIdRange((*found)->getFirstTileId(), (*found)->getFirstTileId() + (*found)->getNbTiles()));
				delete *found;
				tilesets.erase(found);
				refreshTilesetsByTileId();
				dirtyTilesetsByName = true;
			}
		}
	}

	void TileMap::applyTilesetDestruction(const TileIdRange &toDestroy) {
		for (LayerContainer::iterator i = layers.begin(); i != layers.end();
		     ++i) {
			if ((*i)->asTileLayer()) {
				(*i)->asTileLayer()->applyTilesetDestruction(toDestroy);
			}
		}
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
