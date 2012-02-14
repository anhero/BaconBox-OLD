#include "TileLayer.h"

#include "TileMap.h"

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

	void TileLayer::setWidthInTiles(int newWidth, int offset) {
		DataContainer tmpData(data);
	}
}
