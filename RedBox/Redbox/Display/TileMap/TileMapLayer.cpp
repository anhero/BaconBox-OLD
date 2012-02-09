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
}
