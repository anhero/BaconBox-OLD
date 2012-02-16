#include "TileMapLayer.h"

#include <cassert>

#include "TileMap.h"
#include "Color.h"

namespace RedBox {

	void TileMapLayer::setName(const std::string &newName) {
		if (!parentMap.getLayer(newName)) {
			this->TileMapEntity::setName(newName);
			parentMap.dirtyLayersByName = true;
		}
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

	uint8_t TileMapLayer::getOpacity() const {
		return opacity;
	}

	void TileMapLayer::setOpacity(int32_t newOpacity) {
		opacity = Color::getWithinRange(newOpacity);
	}

	bool TileMapLayer::isVisible() const {
		return visible;
	}

	void TileMapLayer::setVisible(bool newVisible) {
		visible = newVisible;
	}

	TileMapLayer::TileMapLayer(const std::string &newName,
	                           const TileMap &newParentMap,
	                           int32_t newOpacity,
	                           bool newVisible) :
		TileMapEntity(newName), parentMap(newParentMap), opacity(0),
		visible(newVisible) {
		setOpacity(newOpacity);
	}

	TileMapLayer::TileMapLayer(const TileMapLayer &src,
	                           const TileMap &newParentMap) :
		TileMapEntity(src), parentMap(newParentMap), opacity(src.opacity),
		visible(src.visible) {
	}

	TileMapLayer::~TileMapLayer() {
	}
}
