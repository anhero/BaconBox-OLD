#include "BaconBox/Display/TileMap/GraphicTileMapLayer.h"

namespace BaconBox {
	GraphicTileMapLayer::GraphicTileMapLayer(const Vector2 &startingPosition) :
		Transformable(startingPosition), Layerable() {
	}

	GraphicTileMapLayer::GraphicTileMapLayer(const GraphicTileMapLayer &src) :
		Transformable(src), Layerable(src) {
	}

	GraphicTileMapLayer::~GraphicTileMapLayer() {
	}

	GraphicTileMapLayer &GraphicTileMapLayer::operator=(const GraphicTileMapLayer &src) {
		this->Transformable::operator=(src);
		this->Layerable::operator=(src);

		return *this;
	}

	GraphicTileLayer *GraphicTileMapLayer::asTileLayer() {
		return NULL;
	}

	const GraphicTileLayer *GraphicTileMapLayer::asTileLayer() const {
		return NULL;
	}

	GraphicObjectLayer *GraphicTileMapLayer::asObjectLayer() {
		return NULL;
	}

	const GraphicObjectLayer *GraphicTileMapLayer::asObjectLayer() const {
		return NULL;
	}
}
