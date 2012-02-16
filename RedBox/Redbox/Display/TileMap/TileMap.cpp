#include "TileMap.h"

#include <cassert>

#include <utility>
#include <algorithm>

#include "Tileset.h"
#include "DeleteHelper.h"
#include "TileMapLayer.h"
#include "TileLayer.h"
#include "ObjectLayer.h"

namespace RedBox {

	TileMap::TileMap(const std::string &newName) : TileMapEntity(newName),
		sizeInTiles(), tileSize(), tilesets(), tilesetsByTileId(),
		tilesetsByName(), dirtyTilesetsByName(false), layers(), layersByName(),
		dirtyLayersByName(false) {
	}

	TileMap::TileMap(const TileMap &src) : TileMapEntity(src),
		sizeInTiles(src.sizeInTiles), tileSize(src.tileSize), tilesets(),
		tilesetsByTileId(), tilesetsByName(), dirtyTilesetsByName(true),
		layers(), layersByName(), dirtyLayersByName(true) {
		// We copy the tilesets.
		for (TilesetContainer::const_iterator i = src.tilesets.begin();
		     i != src.tilesets.end(); ++i) {
			tilesets.push_back(new Tileset(*(*i), *this));
		}

		// We refresh the map of tilesets by tile id's.
		refreshTilesetsByTileId();

		// We copy the layers.
		for (LayerContainer::const_iterator i = src.layers.begin();
		     i != src.layers.end(); ++i) {
			layers.push_back((*i)->clone(*this));
		}
	}

	TileMap::~TileMap() {
		deleteLayers();
		deleteTilesets();
	}

	TileMap &TileMap::operator=(const TileMap &src) {
		this->TileMapEntity::operator=(src);

		if (this != &src) {
			// We clear the layers and the tilesets.
			deleteLayers();
			deleteTilesets();
			tilesets.clear();
			layers.clear();
			// We copy the size in tiles and the tile size.
			sizeInTiles = src.sizeInTiles;
			tileSize = src.tileSize;

			// We copy the tilesets.
			for (TilesetContainer::const_iterator i = src.tilesets.begin();
			     i != src.tilesets.end(); ++i) {
				tilesets.push_back(new Tileset(*(*i), *this));
			}

			// We refresh the map of tilesets by tile id's.
			refreshTilesetsByTileId();

			// We copy the layers.
			for (LayerContainer::const_iterator i = src.layers.begin();
			     i != src.layers.end(); ++i) {
				layers.push_back((*i)->clone(*this));
			}

			// We flag the map of tilesets by their name as dirty.
			dirtyTilesetsByName = true;

			// We do the same for the map of layers by their name.
			dirtyLayersByName = true;
		}

		return *this;
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

	void TileMap::setHeightInTiles(int newHeightInTiles, int offset) {
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

	Tileset *TileMap::getTileset(unsigned int tileId) {
		TilesetMapByTileId::iterator found = tilesetsByTileId.find(tileId);

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

	Tileset *TileMap::addTileset(const std::string &newName,
	                             TexturePointer newTextureInformation,
	                             const Vector2 &newTileSize,
	                             float newTileSpacing,
	                             float newMargin,
	                             const Vector2 &newTileOffset,
	                             bool overwrite) {
		Tileset *result = getTileset(newName);

		if (result) {
			if (overwrite) {
				removeTileset(result);
				addTileset(newName,
				           newTextureInformation.pointer,
				           newTileSize,
				           newTileSpacing,
				           newMargin,
				           newTileOffset,
				           false);

			}

		} else {
			unsigned int firstTileId = (tilesets.empty()) ? (1) : (tilesets.back()->getFirstTileId() + tilesets.back()->getNbTiles());
			tilesets.push_back(new Tileset(newName, *this, newTextureInformation.pointer, newTileSize, newTileSpacing, newMargin, newTileOffset, firstTileId));
			tilesetsByTileId.insert(std::make_pair(TileIdRange(tilesets.back()->getFirstTileId(), tilesets.back()->getFirstTileId() + tilesets.back()->getNbTiles()),
			                                       tilesets.back()));

			result = tilesets.back();

			if (!newName.empty()) {
				dirtyTilesetsByName = true;
			}
		}

		return result;
	}

	void TileMap::removeTileset(const std::string &tilesetName) {
		removeTileset(getTileset(tilesetName));
	}

	void TileMap::removeTileset(const Tileset *tileset) {
		if (tileset) {
			TilesetContainer::iterator found = std::find(tilesets.begin(), tilesets.end(), tileset);

			if (found != tilesets.end()) {
				if (!tileset->getName().empty()) {
					dirtyTilesetsByName = true;
				}

				applyTilesetDestruction(TileIdRange((*found)->getFirstTileId(), (*found)->getFirstTileId() + (*found)->getNbTiles()));
				delete *found;
				tilesets.erase(found);
				refreshTilesetsByTileId();
			}
		}
	}

	const TileMap::LayerContainer &TileMap::getLayers() const {
		return layers;
	}

	const TileMapLayer *TileMap::getLayer(const std::string &layerName) const {
		if (dirtyLayersByName) {
			refreshLayersByName();
		}

		LayerMapByName::const_iterator found = layersByName.find(layerName);

		if (found != layersByName.end()) {
			return found->second;

		} else {
			return NULL;
		}
	}

	TileMapLayer *TileMap::getLayer(const std::string &layerName) {
		if (dirtyTilesetsByName) {
			refreshLayersByName();
		}

		LayerMapByName::iterator found = layersByName.find(layerName);

		if (found != layersByName.end()) {
			return found->second;

		} else {
			return NULL;
		}
	}

	const TileLayer *TileMap::getTileLayer(const std::string &layerName) const {
		if (dirtyLayersByName) {
			refreshLayersByName();
		}

		LayerMapByName::const_iterator found = layersByName.find(layerName);

		if (found != layersByName.end() && found->second->asTileLayer()) {
			return found->second->asTileLayer();

		} else {
			return NULL;
		}
	}

	TileLayer *TileMap::getTileLayer(const std::string &layerName) {
		if (dirtyLayersByName) {
			refreshLayersByName();
		}

		LayerMapByName::iterator found = layersByName.find(layerName);

		if (found != layersByName.end() && found->second->asTileLayer()) {
			return found->second->asTileLayer();

		} else {
			return NULL;
		}
	}

	TileLayer *TileMap::pushBackTileLayer(const std::string &newLayerName,
	                                      int32_t newOpacity,
	                                      bool newVisible,
	                                      bool overwrite) {
		TileMapLayer *result = getLayer(newLayerName);

		if (result) {
			if (overwrite) {
				removeLayer(result);
				pushBackTileLayer(newLayerName, overwrite);
			}

		} else {
			layers.push_back(new TileLayer(newLayerName, *this, newOpacity, newVisible));

			result = layers.back();

			if (!newLayerName.empty()) {
				dirtyLayersByName = true;
			}

			result = layers.back();
		}

		return result->asTileLayer();
	}

	TileLayer *TileMap::pushFrontTileLayer(const std::string &newLayerName,
	                                       int32_t newOpacity,
	                                       bool newVisible,
	                                       bool overwrite) {
		TileMapLayer *result = getLayer(newLayerName);

		if (result) {
			if (overwrite) {
				removeLayer(result);
				pushFrontTileLayer(newLayerName, overwrite);
			}

		} else {
			layers.push_front(new TileLayer(newLayerName, *this, newOpacity, newVisible));

			if (!newLayerName.empty()) {
				dirtyLayersByName = true;
			}

			result = layers.front();
		}

		return result->asTileLayer();
	}

	void TileMap::removeLayer(const std::string &layerName) {
		removeLayer(getLayer(layerName));
	}

	void TileMap::removeLayer(const TileMapLayer *layer) {
		if (layer) {
			LayerContainer::iterator found = std::find(layers.begin(), layers.end(), layer);

			if (found != layers.end()) {
				if (!layer->getName().empty()) {
					dirtyLayersByName = true;
				}

				delete *found;
				layers.erase(found);
			}
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

	void TileMap::refreshTilesetsByName() const {
		tilesetsByName.clear();

		for (TilesetContainer::const_iterator i = tilesets.begin();
		     i != tilesets.end(); ++i) {
			if (!(*i)->getName().empty()) {
				tilesetsByName.insert(std::make_pair((*i)->getName(), *i));
			}
		}
	}

	void TileMap::refreshLayersByName() const {
		layersByName.clear();

		for (LayerContainer::const_iterator i = layers.begin();
		     i != layers.end(); ++i) {
			if (!(*i)->getName().empty()) {
				layersByName.insert(std::make_pair((*i)->getName(), *i));
			}
		}
	}

	void TileMap::applyTilesetDestruction(const TileIdRange &toDestroy) {
		for (LayerContainer::iterator i = layers.begin(); i != layers.end();
		     ++i) {
			(*i)->applyTilesetDestruction(toDestroy);
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
