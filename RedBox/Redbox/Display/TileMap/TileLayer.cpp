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
		unsigned int tmpLength = toDestroy.max - toDestroy.min;

		for (DataContainer::iterator i = data.begin(); i != data.end(); ++i) {
			if (toDestroy.isWithinRange(*i)) {
				*i = 0;

			} else if (*i >= toDestroy.max) {
				*i -= tmpLength;
			}
		}
	}
}
