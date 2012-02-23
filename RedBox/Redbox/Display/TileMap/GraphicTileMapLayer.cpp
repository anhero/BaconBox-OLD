#include "GraphicTileMapLayer.h"

namespace RedBox {
	GraphicTileMapLayer::GraphicTileMapLayer(const Vector2 &startingPosition) :
		Transformable(startingPosition), Layerable() {
	}
	
	GraphicTileMapLayer::~GraphicTileMapLayer() {
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