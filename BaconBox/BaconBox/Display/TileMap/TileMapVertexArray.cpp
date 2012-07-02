#include "BaconBox/Display/TileMap/TileMapVertexArray.h"

#include "BaconBox/Display/TileMap/ObjectLayer.h"

namespace BaconBox {
	void TileMapVertexArray::move(float xDelta, float yDelta) {
		this->TileMapObject::move(xDelta, yDelta);
		getVertices().move(xDelta, yDelta);
	}

	const Vector2 TileMapVertexArray::getCentroid() const {
		return getVertices().getCentroid();
	}

	const Vector2 TileMapVertexArray::getSize() const {
		return getVertices().getSize();
	}

	float TileMapVertexArray::getWidth() const {
		return getVertices().getWidth();
	}

	float TileMapVertexArray::getHeight() const {
		return getVertices().getHeight();
	}

	TileMapVertexArray::TileMapVertexArray(const std::string &newName,
	                                       const Vector2 &newPosition,
	                                       const ObjectLayer &newParentLayer) :
		TileMapObject(newName, newPosition, newParentLayer), Shapable<StandardVertexArray>() {
	}

	TileMapVertexArray::TileMapVertexArray(const TileMapVertexArray &src,
	                                       const ObjectLayer &newParentLayer) :
		TileMapObject(src, newParentLayer), Shapable<StandardVertexArray>(src) {
	}

	TileMapVertexArray::~TileMapVertexArray() {
	}
}
