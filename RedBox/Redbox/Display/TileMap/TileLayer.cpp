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

	void TileLayer::applyTilesetDestruction(const TileIdRange &toDestroy) {
		for (DataContainer::iterator i = data.begin(); i != data.end(); ++i) {
			if (toDestroy.isWithinRange(*i)) {
				*i = 0;
			}
		}
	}
}
