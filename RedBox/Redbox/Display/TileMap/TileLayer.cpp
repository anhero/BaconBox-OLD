#include "TileLayer.h"

namespace RedBox {

	TileLayer *TileLayer::asTileLayer() {
		return this;
	}

	const TileLayer *TileLayer::asTileLayer() const {
		return this;
	}

	TileLayer::~TileLayer() {
	}
}
