#include "TileMapLayer.h"

namespace RedBox {
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
