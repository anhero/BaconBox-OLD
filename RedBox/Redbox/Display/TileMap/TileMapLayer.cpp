#include "TileMapLayer.h"

#include <cassert>

#include "TileMap.h"

namespace RedBox {

	void TileMapLayer::setName(const std::string &newName) {
		this->TileMapEntity::setName(newName);
		assert(parentMap);
		parentMap->dirtyLayersByName = true;
	}

	ObjectLayer *TileMapLayer::asObjectLayer() {
		return NULL;
	}

	const ObjectLayer *TileMapLayer::asObjectLayer() const {
		return NULL;
	}

	TileLayer *TileMapLayer::asTileLayer() {
		return NULL;
	}

	const TileLayer *TileMapLayer::asTileLayer() const {
		return NULL;
	}

	TileMapLayer::TileMapLayer(const TileMap *newParentMap, const std::string &newName) :
		TileMapEntity(newName),
		parentMap(newParentMap) {
	}

	TileMapLayer::~TileMapLayer() {
	}
}
