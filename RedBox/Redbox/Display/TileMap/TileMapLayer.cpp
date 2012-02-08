#include "TileMapLayer.h"

namespace RedBox {
	TileMapLayer::TileMapLayer(const std::string &newName) : Colorable(),
	    Layerable(), Positionable(), TileMapEntity(newName) {
	}

	TileMapLayer::TileMapLayer(const TileMapLayer &src) : Colorable(src),
		Layerable(src), Positionable(src), TileMapEntity(src) {
	}

	TileMapLayer::~TileMapLayer() {
	}

	TileMapLayer &TileMapLayer::operator=(const TileMapLayer &src) {
		this->Colorable::operator=(src);
		this->Layerable::operator=(src);
		this->Positionable::operator=(src);
		this->TileMapEntity::operator=(src);
		return *this;
	}

	ObjectLayer *TileMapLayer::getObjectLayer() {
		return NULL;
	}

	TileLayer *TileMapLayer::getTileLayer() {
		return NULL;
	}
}
